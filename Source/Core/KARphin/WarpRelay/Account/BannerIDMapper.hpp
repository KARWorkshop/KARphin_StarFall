#pragma once

//maps IDs and urls to names for Banners

#include <string>

#include <KARphin/WarpRelay/WarpRelayConnectInfo.hpp>

namespace KARphin::WarpRelay::Account::Banner
{
	#define KAR_BANNER_COUNT 6

	//the names of the banner
static const std::string BANNER_NAMES[KAR_BANNER_COUNT] = {"Pink",      "Carbon", "Orange",
                                                    "Spapphire", "Cherry", "Red"};

	//the urls
static const std::string BANNER_URLS[KAR_BANNER_COUNT] = {
    "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/Pink.banner",
    Connection::WARP_RELAY_CDN_URL + "Carbon" + ".banner",
    Connection::WARP_RELAY_CDN_URL + "Orange" + ".banner",
    Connection::WARP_RELAY_CDN_URL + "Spapphire" + ".banner",
    Connection::WARP_RELAY_CDN_URL + "Cherry" + ".banner",
    Connection::WARP_RELAY_CDN_URL + "Red" + ".banner"};

	//what kind of the banner are they
//static const BannerKind BANNER_KINDS[KAR_BANNER_COUNT] = {
//	BannerKind::Free,
//    BannerKind::Free,
//    BannerKind::Free,
//    BannerKind::Free,
//		BannerKind::Free,
//		BannerKind::Free,
//};
}