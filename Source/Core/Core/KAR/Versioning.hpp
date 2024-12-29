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
#define KAR_VERSION_HOT_FIX "4"
#define KAR_VERSION_BUILD "Star Dust"

// the change log info
#define KAR_CHANGE_LOG_BLURB_TITLE_TEXT "Welcome to KARphin Star Dust!!!!"
#define KAR_CHANGE_LOG_BLURB_INFO_TEXT                                                             \
  "Q: Why is KARphin Updating, hasen't it had enough?\n"                                           \
  "\nA: Yes, it has. But this isn't a normal update. This is a restart for KARphin, taking the "   \
  "notes I learned from the previous builds and taking another shot. "                             \
  "The replays, and other larger changes that caused instability have been removed. "              \
  "Minor tweaks have been kept and some improvements have been made from refactoring the "         \
  "emulator have been kept. \n\n"                                                                  \
  "Q: Why don't you just modified the R10/Legacy build?\n"                                         \
  "\nA: People have a fondness for R10/Legacy and it's the common stable build. "                  \
  "If I released a modified R10 build, it would cause more confusion, and KARphin has already "    \
  "caused enough. "                                                                                \
  "R10/Legacy will stay as it is, I won't be releasing custom R10 builds.\n\n"                     \
  "-----CHANGE LOG " KAR_VERSION_MAJOR "-" KAR_VERSION_MINOR "-" KAR_VERSION_HOT_FIX "-----\n"     \
  "* Warp Relay Accounts now display icons in the Lobby\n"                                         \
  "* Warp Relay Guest Account stock icons thanks to Plantt\n"                                      \
  "* KARphin itself can now auto-update\n"                                                         \
  "* Preconfigured Memory Card for Hack Pack and Backside standard rule set.\n"                    \
  "* Default boot into Debug/Settings Menu \n"                                                     \
  "* Auto FS if \"Auto\" is selected in the Full Screen Code Dropdown, this is default.\n"         \
  "* fair input delay and sync codes forced. Replays have been disabled\n"                         \
  "* players are notified if they lack the game, when joining the Lobby\n"                         \
  "* hide CT FS desync messages\n"                                                                 \
  "* gecko codes are downloadable from inside KARphin\n"                                           \
  "* Netplay Account, Host, and Browser buttons have been added with Taco's custom icons\n"        \
  "* User Settings is forced into local mode and folder is renamed to "                            \
  "\"StarDust_Player_Settings\"\n"                                                                 \
  "* ROMs can only be loaded via the ROMs folder\n"                                                \
  "* Controller Profiles are loaded from the Profiles folder in the Accounts folder.\n"            \
  "* Minor tweaks\n"                                                                               \
  "\n\nFor a full list of changes check out the " KAR_VERSION_BUILD                                \
  " branch on the github: \"https://github.com/KARWorkshop/KARphin_StarFall\""
}  // namespace Core
}  // namespace KAR