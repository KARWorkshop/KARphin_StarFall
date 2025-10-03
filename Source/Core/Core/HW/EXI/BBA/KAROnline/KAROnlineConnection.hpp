#pragma once

//defines a connection, this can be either the host or client

#include <Core/HW/EXI/BBA/KAROnline/NetConfig.hpp>

#include <Common/Logging/Log.h>

namespace KAR::Online
{
	//defines the connection
	struct KARConnection
	{
		//inits the connection || takes in the net info for ourself
		inline bool Connect(const NetInfo& self)
		{
      SteamDatagramErrMsg errMsg;
      if (!GameNetworkingSockets_Init(nullptr, errMsg))
      {
        return false;
        // FatalError("GameNetworkingSockets_Init failed.  %s", errMsg);
			}

			INFO_LOG_FMT(SP1, "Game Networking Sockets inited!");

			return true;
		}
	};
}