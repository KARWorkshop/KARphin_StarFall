#pragma once

//handles netplay interactions

#include <KAR/Netplay/Socket/KARClient.hpp>
#include <KAR/Netplay/Socket/KARServer.hpp>

#include <KAR/Netplay/NetworkBackend.hpp>

namespace KAR::Networking
{
	//defines a netplay config file
	struct NetplayConfig
	{
    Util::NetworkConnectionType connectMode = Util::NetworkConnectionType::Online_HostCode; //the mode we are using
	};

	//defines a netplay manager
}