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

    bool isRunning = false;

    // starts hosting a instance
    bool Host(ISteamNetworkingSockets* steamNetworkingInterface, const NetInfo& self);

    // shutsdown the connection
    void Shutdown(ISteamNetworkingSockets* steamNetworkingInterface);
	};
}