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

    bool isRunning = false;

    //the actual function for handling connection state changes
    void OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pInfo);

    // starts hosting a instance
    bool Host(ISteamNetworkingSockets* _steamNetworkingInterface, const NetInfo& self);

    // shutsdown the connection
    void Shutdown();
	};
}