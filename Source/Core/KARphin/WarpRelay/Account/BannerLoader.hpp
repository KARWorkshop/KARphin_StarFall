#pragma once

//this handles loading and caching the Banners for all players in a lobby

#include <string>
#include <vector>

namespace KARphin::WarpRelay::Account
{
	//gets the size for the icons
static const int BANNER_ICON_SIZE_WIDTH = 80;
static const int BANNER_ICON_SIZE_HEIGHT = 80;

//gets the Icon data based on a URL, if it doesn't exist, load it
std::vector<uint8_t>& GetIcon(const std::string& URL);

}