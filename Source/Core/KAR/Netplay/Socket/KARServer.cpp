#include <KAR/Netplay/Socket/KARServer.hpp>

#include <KAR/Netplay/NetworkBackend.hpp>

#include <Common/ENet.h>

#include <iostream>

// thread func for commands
void KAR::Networking::Core::NetPlayServer::ThreadFunc()
{

}

void KAR::Networking::Core::NetPlayServer::Init()
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
  //if (traversal)
 // {
    if (!Common::EnsureTraversalClient(Util::GetSTUNServer_Address_Dolphin(),
                                       Util::GetSTUNServer_Port_Dolphin(), 4201))
      return;

    Common::g_TraversalClient->m_Client = this;
    m_traversal_client = Common::g_TraversalClient.get();

    m_server = Common::g_MainNetHost.get();

    if (Common::g_TraversalClient->GetState() == Common::TraversalClient::State::Failure)
      Common::g_TraversalClient->ReconnectToServer();
 // }

  //if in direct connect mode
 // else
 // {
 //   ENetAddress serverAddr;
 //   serverAddr.host = ENET_HOST_ANY;
 //   serverAddr.port = 4201;
 //   m_server = enet_host_create(&serverAddr, 10, 3, 0, 0);
 //   if (m_server != nullptr)
 //     m_server->intercept = Common::ENet::InterceptCallback;
 // }

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
