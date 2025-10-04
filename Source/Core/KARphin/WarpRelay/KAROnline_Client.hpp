#pragma once

//defines a instance of the client for connecting to a host

#include <Core/HW/EXI/BBA/KAROnline/NetConfig.hpp>

#include <Common/Logging/Log.h>

namespace KAR::Online::Netplay
{
	//defines a client
	struct ClientInstance
	{
    HSteamNetConnection m_hConnection = k_HSteamNetConnection_Invalid;
    ISteamNetworkingSockets* steamNetworkingInterface;

    bool shouldDisconnect = false; //should we disconnect from the connection

    bool isRunning = false;

    //connects to a host
    bool Connect(ISteamNetworkingSockets* _steamNetworkingInterface, const NetInfo& target);

    // shutsdown the connection
    void Shutdown();

    // the actual function for when the connection state changes
    void OnSteamNetConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* pInfo);
	};
}