#pragma once

//this handles loading and caching the Banners for all players in a lobby

#include <KARphin/WarpRelay/Account/WarpRelayConnection_Banners.hpp>

#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <map>

namespace KARphin::WarpRelay::Account
{
// gets the size for the icons
static const int BANNER_ICON_SIZE_WIDTH = 80;
static const int BANNER_ICON_SIZE_HEIGHT = 80;

//defines a loader that runs in another thread for the icons
struct BannerLoader
{
  std::map<std::string, std::vector<uint8_t>>
      banners;  //stores the raw banner info

	static BannerLoader& Instance()
	{
		static BannerLoader instance;
    return instance;
	}

  //downloads a banner info from the server
  std::vector<uint8_t> DownloadBanner(const std::string& URL);

  //gets a icon data
  inline std::vector<uint8_t>& GetIcon(const std::string& URL)
  {
    if (banners.find(URL) == banners.end())
    {
      banners[URL] = DownloadBanner(URL);
    }
    return banners.at(URL);
  }

};

}