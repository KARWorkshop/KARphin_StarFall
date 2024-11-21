#pragma once

//defines data about the Warp Relay user on this system

#include <Core/KAR/json.hpp>

#include <Common/FileUtil.h>

namespace KAR::WarpRelay
{
#define WARP_RELAY_USER_ACCOUNT_API_VERSION "1.0.0"

	//returns the path to the folder containing all the Warp Relay Accounts
	static inline std::string GetFolderContainingAllWarpRelayAccountFiles()
	{
    return File::GetExeDirectory() + "/../Accounts";
	}

	//returns the file extention for a warp relay account file
  static inline std::string GetWarpRelayAccountFileExtension()
  {
    return ".wra";
  }

	//defines the region
  enum class Region
  {
    NA,
    PAL,
    Asia,

    Count
  };

	//defines the rank level || used on the local rank latter
  enum class Rank
  {
    StarDust = 0,

    WhiteHole
  };

	//defines the data loaded from a warp relay file
	struct WarpRelayAccount
	{
    bool isGuestAccount = true; //guest accounts don't get paid sub-features

    std::string displayName = "Kirby",  // the display name used online
        customIconURL = "",  // the URL/local path to the custom icon if they have one

        discordAccountLinkHash = "",  // the hash we use to validate they have a linked discord account
        googleAccountLinkHash = "",// the hash we use to validate they have a linked google account
        warpRelayAccountHash = "";  // the hash we use to validate they have a Warp Relay account and aren't just a guest
	};

  //writes it to disc
  static inline void WriteWarpRelayAccount(const WarpRelayAccount& account)
  {
    const std::string accountPath = GetFolderContainingAllWarpRelayAccountFiles() + "/" +
                                    account.displayName + GetWarpRelayAccountFileExtension();

    nlohmann::json j;
    j["version"] = WARP_RELAY_USER_ACCOUNT_API_VERSION;
    j["displayName"] = account.displayName;
    j["warpRelayHash"] = account.warpRelayAccountHash;
    j["customIcon"] = account.customIconURL;

    File::CreateEmptyFile(accountPath);
    File::WriteStringToFile(accountPath, j.dump());
  }

	//loads a Warp Relay Account file
  static inline WarpRelayAccount LoadWarpRelayAccount(const std::string& accountFP)
	{
    std::string str = "";
    if (!File::Exists(accountFP) ||
        !File::ReadFileToString(accountFP, str))
    {
      return WarpRelayAccount(); //return a NULL file here
    }

		//parse out the file data
    WarpRelayAccount account;
    nlohmann::json j = nlohmann::json::parse(str);

    if (j["version"] != WARP_RELAY_USER_ACCOUNT_API_VERSION)
    {
      account.displayName = "DATA_IS_OUTOFDATE_API";
      return account;
    }


    account.displayName = j["displayName"];
    account.warpRelayAccountHash = j["warpRelayHash"];
    account.customIconURL = j["customIcon"];

    //make a call to validate if they're a guest || for now we force everyone to be a guest
    account.isGuestAccount = true;

    return account;
	}
}