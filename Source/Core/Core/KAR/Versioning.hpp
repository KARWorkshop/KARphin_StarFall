#pragma once

//defines versioning data for this build

#include <Core/KAR/json.hpp>

#include <Common/FileUtil.h>

namespace KAR
{
	namespace Core
	{
		//stores the legacy version string for KARphin Legacy and R10
#define LEGACY_R10_VERSION_STRING "50f504eb710d1b1e74356e75f8fbef310b811951"

	//types of builds
#define KAR_VERSION_STABLE_STR "Stable"
#define KAR_VERSION_DEV_STR "Dev"

		//client data
#define KAR_VERSION_MAJOR "1"
#define KAR_VERSION_MINOR "0"
#define KAR_VERSION_HOT_FIX "0"
#define KAR_VERSION_BUILD "Star Dust"
#define KAR_VERSION_STABILITY KAR_VERSION_DEV_STR

		//the change log info
#define KAR_CHANGE_LOG_BLURB_TITLE_TEXT "Welcome to KARphin Star Dust!!!!"
#define KAR_CHANGE_LOG_BLURB_INFO_TEXT "Q: Why is KARphin Updating, hasen't it had enough?\n" \
  "\nA: Yes, it has. But this isn't a normal update. This is a restart for KARphin, taking the notes I learned from the previous builds and taking another shot. " \
  "The auto fullscreen codes, replays, and other larger changes that caused instability have been removed. " \
	"Minor tweaks have been kept and some improvements have been made from refactoring the emulator have been kept. \n\n" \
	"Q: Without the auto-FS, what's the point? Why keep the emulator?\n" \
	"\nA: The feature set is removed for now. They will be coming back eventually. For now this gives us a stable KARphin build. " \
	"Updates will come out.\n\n" \
	"Q: Why don't you just modified the R10/Legacy build?\n" \
	"\nA: People have a fondness for R10/Legacy and it's the common stable build. " \
	"If I released a modified R10 build, it would cause more confusion, and KARphin has already caused enough. " \
	"R10/Legacy will stay as it is, I won't be releasing custom R10 builds.\n\n" \
	"-----CHANGE LOG " \
	KAR_VERSION_MAJOR \
  "-" \
  KAR_VERSION_MINOR \
	"-" \
	KAR_VERSION_HOT_FIX \
	"-----\n" \
	/*"* KARphin itself can now auto-update\n"*/ \
	"* Default boot into Debug/Settings Menu \n" \
	"* FS Codes have been moved into a selectable drop down when using a supported ROM\n" \
	"* Auto FS if \"Auto\" is selected in the Full Screen Code Dropdown, this is default.\n" \
	"* fair input delay and sync codes forced. Replays have been disabled\n" \
	"* players are notified if they lack the game, when joining the Lobby\n" \
	"* hide CT FS desync messages\n" \
	"* gecko codes are downloadable from inside KARphin\n" \
	"* Netplay Account, Host, and Browser buttons have been added with Taco's custom icons\n" \
	"* User Settings is forced into local mode and folder is renamed to \"StarDust_Player_Settings\"\n" \
	"* ROMs can only be loaded via the ROMs folder\n" \
	"* Controller Profiles are loaded from the Profiles folder in the Accounts folder.\n" \
	"* Minor tweaks\n" \
	"\n\nFor a full list of changes check out the " \
	KAR_VERSION_BUILD \
	" branch on the github: \"https://github.com/KARWorkshop/KARphin_StarFall\""

		//defines the build data
		struct BuildData
		{
      std::string majorVer = "NULL", minorVer = "", hotfix = "", build = "";
      bool hasSeenChangeLog = false;
		};

		//writes the version data to a file
		static inline void WriteBuildVersionDataToFile(bool hasSeenChangeLog)
		{
	        nlohmann::json j;
	        j["ver_major"] = KAR_VERSION_MAJOR;
	        j["ver_minor"] = KAR_VERSION_MINOR;
	        j["ver_hotfix"] = KAR_VERSION_HOT_FIX;
	        j["build"] = KAR_VERSION_BUILD;
          j["hasSeenChangeLog"] = hasSeenChangeLog;

					File::CreateEmptyFile(File::GetExeDirectory() + "/build.stt");
          File::WriteStringToFile(File::GetExeDirectory() + "/build.stt", j.dump());
		}

		//loads the version data from a file
    static inline BuildData LoadBuildVersionDataFromFile()
    {
      std::string str = "";
      if (!File::Exists(File::GetExeDirectory() + "/build.stt") ||
          !File::ReadFileToString(File::GetExeDirectory() + "/build.stt", str))
			{
        return BuildData();
			}

			BuildData d;
      nlohmann::json j = nlohmann::json::parse(str);
      d.majorVer = j["ver_major"];
      d.minorVer = j["ver_minor"];
      d.hotfix = j["ver_hotfix"];
      d.build = j["build"];
      d.hasSeenChangeLog = j["hasSeenChangeLog"];

      return d;
    }

		//checks the build's version against the latest build, and updates if it's out of date
	}
}