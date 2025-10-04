#pragma once

//defines a server that a host will spin up to handle connections

#include <Core/HW/EXI/BBA/KAROnline/NetConfig.hpp>

#include <Common/Logging/Log.h>

namespace KAR::Online::Netplay
{
	//defines a host
	struct HostServerInstance
	{
    HSteamListenSocket listenSocket = k_HSteamListenSocket_Invalid;
    HSteamNetPollGroup pollGroup = k_HSteamNetPollGroup_Invalid;
    ISteamNetworkingSockets* steamNetworkingInterface;

    //clents that connected to us
    struct Client_t
    {
      std::string m_sNick;
    };
    std::map<HSteamNetConnection, Client_t> m_mapClients;

    bool isRunning = false;

    //the actual function for handling connection state changes
    void OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pInfo);

    // starts hosting a instance
    bool Host(ISteamNetworkingSockets* _steamNetworkingInterface, const NetInfo& self);

    // shutsdown the connection
    void Shutdown();

    //sends a string to a specific client
    void SendStringToClient(HSteamNetConnection conn, const char* str)
    {
      steamNetworkingInterface->SendMessageToConnection(conn, str, (uint32)strlen(str),
                                            k_nSteamNetworkingSend_Reliable, nullptr);
    }

    //sends a string to every client
    void SendStringToAllClients(const char* str,
                                HSteamNetConnection except = k_HSteamNetConnection_Invalid)
    {
      for (auto& c : m_mapClients)
      {
        if (c.first != except)
          SendStringToClient(c.first, str);
      }
    }

    //sets the nickname of the client connection
    void SetClientNick(HSteamNetConnection hConn, const char* nick)
    {
      // Remember their nick
      m_mapClients[hConn].m_sNick = nick;

      // Set the connection name, too, which is useful for debugging
      steamNetworkingInterface->SetConnectionName(hConn, nick);
    }
	};
}