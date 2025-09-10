#pragma once

//maps to a enum to a URL for the player icons/Banner
//this includes getting a Player's custom Banner

#include <string>

namespace KARphin::WarpRelay::Account
{
	//defines the kind of Banner
	enum class BannerKind
	{
		Preset= 0, //will just grab the preset icons

		DiscordIcon, //will snag your Discord Icon and use that || only useable by subscribers
		CustomIcon, //will let you set whatever Icon you want || only useable by subscribers

		Count
	};

	// defines a name for all the color presets and their URL
#define WR_PRESET_BANNER_COUNT 4
  static const char* WR_PRESET_BANNER_NAMES[WR_PRESET_BANNER_COUNT] = {"Pink", "Red", "Silver",
                                                                       "Mint"};
  static const char* WR_PRESET_BANNER_URLS[WR_PRESET_BANNER_COUNT] =
	{"https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/Pink.png",
		"https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/Red.png",
		"https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/Silver.png",
  "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/Mint.png"};

  }