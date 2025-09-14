#pragma once

//just some common structs and info needed for connecting to the Warp Relay

#include <string>

namespace KARphin::WarpRelay::Connection
{
	//the base URL for accessing the Warp Relay
static const std::string WARP_RELAY_API_URL = "https://karworkshop.com";

//the base URL for accessing the CDN for Banners
static const std::string WARP_RELAY_CDN_URL =
    "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/";
}