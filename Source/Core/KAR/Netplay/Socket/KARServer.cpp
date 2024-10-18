#include <KAR/Netplay/Socket/KARServer.hpp>

#include <memory>
#include <string>
#include <vector>
#include "Common/Common.h"
#include <Common/ENet.h> ///Common/ENetUtil.h"
#include "Common/FileUtil.h"
#include "Common/IniFile.h"
#include "Common/Logging/Log.h"
#include "Common/MsgHandler.h"
#include "Common/StringUtil.h"
#include "Core/ConfigManager.h"
#include <Core/HW/EXI/EXI_DeviceIPL.h> //Core/HW/EXI_DeviceIPL.h"
#include "Core/HW/Sram.h"
#include "InputCommon/GCPadStatus.h"
#if !defined(_WIN32)
#include <sys/socket.h>
#include <sys/types.h>
#ifndef ANDROID
#include <ifaddrs.h>
#endif
#include <arpa/inet.h>
#endif

u64 g_netplay_initial_rtc = 1272737767;

#include <KAR/Netplay/NetworkBackend.hpp>

#include <Common/ENet.h>

#include <iostream>

// thread func for commands
void KAR::Networking::Core::NetPlayServer::ThreadFunc()
{
  while (m_do_loop)
  {
    // update pings every so many seconds
    if ((m_ping_timer.ElapsedMs() > 250) || m_update_pings)
    {
      // only used as an identifier, not time value, so truncation is fine
      m_ping_key = static_cast<u32>(Common::Timer::NowMs());

      sf::Packet spac;
      spac << (u8)(NetPlay::MessageID)NetPlay::MessageID::Ping;
      spac << m_ping_key;

      m_ping_timer.Start();
      SendToClients(spac);
      m_update_pings = false;
    }

    ENetEvent netEvent;
    int net;
    if (m_traversal_client)
      m_traversal_client->HandleResends();
    net = enet_host_service(m_server, &netEvent, 1000);
    while (!m_async_queue.Empty())
    {
      {
        std::lock_guard<std::recursive_mutex> lkp(m_crit.players);
        SendToClients(*(m_async_queue.Front().get()));
      }
      m_async_queue.Pop();
    }
    if (net > 0)
    {
      switch (netEvent.type)
      {
      case ENET_EVENT_TYPE_CONNECT:
      {
        ENetPeer* accept_peer = netEvent.peer;
        unsigned int error;
        {
          std::lock_guard<std::recursive_mutex> lkg(m_crit.game);
          error = OnConnect(accept_peer);
        }

        if (error)
        {
          sf::Packet spac;
          spac << (u8)(NetPlay::MessageID)error;
          // don't need to lock, this client isn't in the client map
          Send(accept_peer, spac);
          if (netEvent.peer->data)
          {
            delete (NetPlay::PlayerId*)netEvent.peer->data;
            netEvent.peer->data = nullptr;
          }
          enet_peer_disconnect(accept_peer, 0);
        }
      }
      break;
      case ENET_EVENT_TYPE_RECEIVE:
      {
        sf::Packet rpac;
        rpac.append(netEvent.packet->data, netEvent.packet->dataLength);

        auto it = m_players.find(*(NetPlay::PlayerId*)netEvent.peer->data);
        Client& client = it->second;
        if (OnData(rpac, client) != 0)
        {
          // if a bad packet is received, disconnect the client
          std::lock_guard<std::recursive_mutex> lkg(m_crit.game);
          OnDisconnect(client);

          if (netEvent.peer->data)
          {
            delete (NetPlay::PlayerId*)netEvent.peer->data;
            netEvent.peer->data = nullptr;
          }
        }
        enet_packet_destroy(netEvent.packet);
      }
      break;
      case ENET_EVENT_TYPE_DISCONNECT:
      {
        std::lock_guard<std::recursive_mutex> lkg(m_crit.game);
        if (!netEvent.peer->data)
          break;
        auto it = m_players.find(*(NetPlay::PlayerId*)netEvent.peer->data);
        if (it != m_players.end())
        {
          Client& client = it->second;
          OnDisconnect(client);

          if (netEvent.peer->data)
          {
            delete (NetPlay::PlayerId*)netEvent.peer->data;
            netEvent.peer->data = nullptr;
          }
        }
      }
      break;
      default:
        break;
      }
    }
  }

  // close listening socket and client sockets
  for (auto& player_entry : m_players)
  {
#ifdef _WIN32
    if (player_entry.second.qos_handle != 0)
    {
      if (player_entry.second.qos_flow_id != 0)
        QOSRemoveSocketFromFlow(player_entry.second.qos_handle,
                                player_entry.second.socket->host->socket,
                                player_entry.second.qos_flow_id, 0);
      QOSCloseHandle(player_entry.second.qos_handle);
    }
#endif

    delete (NetPlay::PlayerId*)player_entry.second.socket->data;
    player_entry.second.socket->data = nullptr;
    enet_peer_disconnect(player_entry.second.socket, 0);
  }
}

void KAR::Networking::Core::NetPlayServer::Init(const KAR::Networking::Util::NetworkConnectionType connectMode)
{
  //--use server time
  if (enet_initialize() != 0)
  {
    //PanicAlertT("Enet Didn't Initialize");

    std::cout << "ENet didn't initalize!" << std::endl;
    return;
  }

  m_pad_map.fill(-1);
  m_wiimote_map.fill(-1);

  //if we're in traversal mode
  if (connectMode == KAR::Networking::Util::NetworkConnectionType::Online_HostCode)
  {
    if (!Common::EnsureTraversalClient(Util::GetSTUNServer_Address_Dolphin(),
                                       Util::GetSTUNServer_Port_Dolphin(), 4201))
      return;

    Common::g_TraversalClient->m_Client = this;
    m_traversal_client = Common::g_TraversalClient.get();

    m_server = Common::g_MainNetHost.get();

    if (Common::g_TraversalClient->GetState() == Common::TraversalClient::State::Failure)
      Common::g_TraversalClient->ReconnectToServer();
  }

  //if in direct connect mode
  else if (connectMode == KAR::Networking::Util::NetworkConnectionType::Direct_IP)
  {
    ENetAddress serverAddr;
    serverAddr.host = ENET_HOST_ANY;
    serverAddr.port = 4201;
    m_server = enet_host_create(&serverAddr, 10, 3, 0, 0);
    if (m_server != nullptr)
      m_server->intercept = Common::ENet::InterceptCallback;
  }

  //if the server was created
  if (m_server != nullptr)
  {
    is_connected = true;
    m_do_loop = true;
    m_thread = std::thread(&NetPlayServer::ThreadFunc, this);
    m_minimum_buffer_size = 8;
  }

  std::cout << "Server initalized" << std::endl;
}

void KAR::Networking::Core::NetPlayServer::Shutdown()
{
  if (is_connected)
  {
    m_do_loop = false;
    m_thread.join();
    enet_host_destroy(m_server);

    if (Common::g_MainNetHost.get() == m_server)
    {
      Common::g_MainNetHost.release();
    }

    if (m_traversal_client)
    {
      Common::g_TraversalClient->m_Client = nullptr;
      Common::ReleaseTraversalClient();
    }
  }

#ifdef USE_UPNP
  if (m_upnp_thread.joinable())
    m_upnp_thread.join();
  m_upnp_thread = std::thread(&NetPlayServer::unmapPortThread);
  m_upnp_thread.join();
#endif
}
