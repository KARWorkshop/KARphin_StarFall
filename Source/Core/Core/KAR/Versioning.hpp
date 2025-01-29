#pragma once

//defines versioning data for this build

#include <Core/KAR/json.hpp>

#include <Common/FileUtil.h>

namespace KAR
{
namespace Core
{
// stores the legacy version string for KARphin Legacy and R10
#define LEGACY_R10_VERSION_STRING "50f504eb710d1b1e74356e75f8fbef310b811951"

// client data
#define KAR_VERSION_MAJOR "3"
#define KAR_VERSION_MINOR "0"
#define KAR_VERSION_HOT_FIX "14"
#define KAR_VERSION_BUILD "Star Dust"

  //used in lobby string
#define KAR_VERSION_STRING_LOBBY std::string(KAR_VERSION_MAJOR) + "." + KAR_VERSION_MINOR

    //full version string
#define KAR_VERSION_FULL_STRING std::string(KAR_VERSION_MAJOR) + "." + KAR_VERSION_MINOR + "." + KAR_VERSION_HOT_FIX

// the change log info
#define KAR_CHANGE_LOG_BLURB_TITLE_TEXT "Welcome to KARphin Star Dust!!!!"
#define KAR_CHANGE_LOG_BLURB_INFO_TEXT \
  "\n-----CHANGE LOG " KAR_VERSION_MAJOR "." KAR_VERSION_MINOR "." KAR_VERSION_HOT_FIX "-----\n"   \
  "* Players can join as Spectators.\n"                                                                                       \
  "* Prelimary shock collar support.\n"                                \
  "* Prelimary betting support. \n"   \
  "\n-----CHANGE LOG 3.0.13 -----\n"     \
  "* Fixed lobby version string, so if major and minor version are the same. You can join the lobby.\n"   \
  "* Merged netplay core codes into \"KARphin Core Netplay V1\".\n"   \
  "* About section properly displays version string. \n"   \
  "\n-----CHANGE LOG 3.0.12 -----\n"     \
  "* Added more Account stock icons, Backside themed, thanks Taco :3.\n"                                         \
  "\n-----CHANGE LOG 3.0.11 -----\n"     \
  "* KARphin now properly loads extracted ROMs.\n"                                         \
  "\n-----CHANGE LOG 3.0.10 -----\n"     \
  "* Warp Relay Accounts now display icons in the Lobby.\n"                                         \
  "* Warp Relay Guest Account stock icons thanks to Plantt.\n"                                      \
  "* Warp Relay Non-Guest Accounts can set their own icons.\n"                                     \
  "* KARphin itself can now auto-update.\n"                                                         \
  "* Preconfigured Memory Card for Hack Pack and Backside standard rule set.\n"                    \
  "* Default boot into Debug/Settings Menu.\n"                                                     \
  "* Auto FS if \"Auto\" is selected in the Full Screen Code Dropdown, this is default.\n"         \
  "* fair input delay and sync codes forced. Replays have been disabled.\n"                         \
  "* players are notified if they lack the game, when joining the Lobby.\n"                         \
  "* hide CT FS desync messages.\n"                                                                 \
  "* gecko codes are downloadable from inside KARphin.\n"                                           \
  "* Netplay Account, Host, and Browser buttons have been added with Taco's custom icons.\n"        \
  "* User Settings is forced into local mode and folder is renamed to "                            \
  "\"StarDust_Player_Settings\".\n"                                                                 \
  "* ROMs can only be loaded via the ROMs folder.\n"                                                \
  "* Controller Profiles are loaded from the Profiles folder in the Accounts folder.\n"            \
  "* Minor tweaks.\n"                                                                               \
  "\n\nFor a full list of changes check out the " KAR_VERSION_BUILD                                \
  " branch on the github: \"https://github.com/KARWorkshop/KARphin_StarFall\""
}  // namespace Core
}  // namespace KAR