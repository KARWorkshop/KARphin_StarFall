#pragma once

//defines a object and functions for connecting to warp relay and getting info or urls for banners

#include <string>

#include <KARphin/WarpRelay/WarpRelayConnectInfo.hpp>

namespace KARphin::WarpRelay::Account::Banner
{
	//gets a image URL
	static inline std::string GetBannerURL(const uint64_t& ID)
	{
    return Connection::WARP_RELAY_CDN_URL + std::to_string(ID) + ".banner";
	}

	//gets the info for a Banner Image
	static inline std::string GetBannerInfo(const uint64_t& ID)
	{
  // return "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/" +
  //        std::to_string(ID) + ".banner";
  return "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/"
         "0.banner";
	}
}