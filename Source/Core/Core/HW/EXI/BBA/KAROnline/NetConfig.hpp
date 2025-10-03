#pragma once

/*
Net Config Data - this is a small file/struct that stores the info this runner uses for connecting with the BBA
									this data is normally written by the KAR Online frontend/launcher
*/

#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>

namespace KAR::Online
{
	//defines the net info data
	struct NetInfo
	{
    bool isHost = false; //is this instance a host or client
    uint16_t listeningPort = 6969; //the port we listen on

	};
}