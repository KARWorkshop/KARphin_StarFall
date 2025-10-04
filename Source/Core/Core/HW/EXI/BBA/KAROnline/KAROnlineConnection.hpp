#pragma once

//defines a connection, this can be either the host or client

#include <Core/HW/EXI/BBA/KAROnline/NetConfig.hpp>

#include <Common/Logging/Log.h>

namespace KAR::Online
{
	//defines the connection
	struct KARConnection
	{
    HSteamListenSocket listenSocket = k_HSteamListenSocket_Invalid;
    HSteamNetPollGroup pollGroup = k_HSteamNetPollGroup_Invalid;

		//inits the connection || takes in the net info for ourself
    inline bool Connect(ISteamNetworkingSockets* steamNetworkingInterface, const NetInfo& self)
		{
			// Start listening
      SteamNetworkingIPAddr serverLocalAddr;
      serverLocalAddr.Clear();
      serverLocalAddr.m_port = self.listeningPort;
      SteamNetworkingConfigValue_t opt;
      opt.SetPtr(k_ESteamNetworkingConfig_Callback_ConnectionStatusChanged, nullptr);
                 //(void*)SteamNetConnectionStatusChangedCallback);
      listenSocket = steamNetworkingInterface->CreateListenSocketIP(serverLocalAddr, 1, &opt);
      if (listenSocket == k_HSteamListenSocket_Invalid)
        ERROR_LOG_FMT(SP1, "Failed to listen on port {}", self.listeningPort);
      pollGroup = steamNetworkingInterface->CreatePollGroup();
      if (pollGroup == k_HSteamNetPollGroup_Invalid)
        ERROR_LOG_FMT(SP1, "Failed to listen on port {}", self.listeningPort);
     INFO_LOG_FMT(SP1, "Server listening on port {}\n", self.listeningPort);

			return true;
		}

    //shutsdown the connection
    inline void Shutdown(ISteamNetworkingSockets* steamNetworkingInterface)
    {
      INFO_LOG_FMT(SP1, "Server Shutdown");

      steamNetworkingInterface->CloseListenSocket(listenSocket);
      listenSocket = k_HSteamListenSocket_Invalid;

      steamNetworkingInterface->DestroyPollGroup(pollGroup);
      pollGroup = k_HSteamNetPollGroup_Invalid;
    }

  };
}