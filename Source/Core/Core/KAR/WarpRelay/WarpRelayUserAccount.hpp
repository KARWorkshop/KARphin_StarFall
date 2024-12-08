#pragma once

//defines data about the Warp Relay user on this system

#include <Core/KAR/json.hpp>

#include <Common/FileUtil.h>
#include <Common/FileSearch.h>

namespace KAR::WarpRelay
{
#define WARP_RELAY_USER_ACCOUNT_API_VERSION "1.0.0"

	//returns the path to the folder containing all the Warp Relay Accounts
	static inline std::string GetAccountsDir()
	{
    const std::string p = File::GetExeDirectory() + "/../Accounts/";
    if (!File::Exists(p))
      File::CreateDir(p);

    return p;
	}

	//returns the file extention for a warp relay account file
  static inline std::string GetWarpRelayAccountFileExtension()
  {
    return ".wra";
  }

  // gets every account file
  static inline std::vector<std::string> GetAllAccountFiles()
  {
    return Common::DoFileSearch({GetAccountsDir()}, {GetWarpRelayAccountFileExtension()});
  }

	//defines the region
  enum class Region : uint8_t
  {
    EA = 0x00, //East Asia
    CN, //China
    EU, // Europe
    NA, // North America
    SA, // South America
    OC, //Oceania
    AF, // Africa

    Count
  };

  //converts into a region string
  static inline std::string GetRegionStr(const Region& region)
  {
    switch (region)
    {
    case Region::EA:
      return "EA";
    case Region::CN:
      return "CN";
    case Region::EU:
      return "EU";
    case Region::NA:
      return "NA";
    case Region::SA:
      return "SA";
    case Region::OC:
      return "OC";
    case Region::AF:
      return "AF";
    }

    return std::string();
  }

  // converts into a region string
  static inline std::string GetRegionLongStr(const Region& region)
  {
    switch (region)
    {
    case Region::EA:
      return "East Asia";
    case Region::CN:
      return "China";
    case Region::EU:
      return "Europe";
    case Region::NA:
      return "North America";
    case Region::SA:
      return "South America";
    case Region::OC:
      return "Oceania";
    case Region::AF:
      return "Africa";
    }

    return std::string();
  }

  //converts into a region enum
  static inline Region GetRegionByte(const std::string& str)
  {
    if (str == "East Asia")
      return Region::EA;
    else if(str == "China")
      return Region::CN;
    else if (str == "Europe")
      return Region::EU;
    else if (str == "North America")
      return Region::NA;
    else if (str == "South America")
      return Region::SA;
    else if (str == "Oceania")
      return Region::OC;
    else if (str == "Africa")
      return Region::AF;

    return Region::Count;
  }

	//defines the rank level || used on the local rank latter
  enum class Rank : uint8_t
  {
    StarDust = 0x00,

    WhiteHole,

    Count
  };

  static inline std::string GetRankStr(const Rank& rank)
  {
    return "Star Dust";
  }

	//defines the data loaded from a warp relay file
	struct WarpRelayAccount
	{
    bool isGuestAccount = true; //guest accounts don't get paid sub-features

    Rank rank = Rank::StarDust; //defines the temp latter rank of the user
    Region region = Region::NA;  // the geo-region to use

    std::string displayName = "Kirby",  // the display name used online
      customIconURL = "",  // the URL/local path to the custom icon if they have one
      username = "Guest", //the user name, used for loading the file
        discordAccountLinkHash = "",  // the hash we use to validate they have a linked discord account
        googleAccountLinkHash = "",// the hash we use to validate they have a linked google account
        warpRelayAccountHash = "";  // the hash we use to validate they have a Warp Relay account and aren't just a guest
	};

  //writes it to disc
  static inline void WriteWarpRelayAccount(const WarpRelayAccount& account)
  {
    const std::string accountPath = GetAccountsDir() + account.username + GetWarpRelayAccountFileExtension();

    nlohmann::json j;
    j["version"] = WARP_RELAY_USER_ACCOUNT_API_VERSION;
    j["isGuest"] = account.isGuestAccount;
    j["displayName"] = account.displayName;
    j["warpRelayHash"] = account.warpRelayAccountHash;
    j["customIcon"] = account.customIconURL;
    j["username"] = account.username;

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

    if (!j.contains("version") || j["version"] != WARP_RELAY_USER_ACCOUNT_API_VERSION)
    {
      account.displayName = "DATA_IS_OUTOFDATE_API";
      return account;
    }

    account.isGuestAccount = (j.contains("isGuest") ? j["isGuest"].get<bool>() : true);
    account.displayName = (j.contains("displayName") ? j["displayName"] : "Kirby");
    account.warpRelayAccountHash = (j.contains("warpRelayHash") ? j["warpRelayHash"] : "");
    account.customIconURL = (j.contains("customIcon") ? j["customIcon"] : "");
    account.username = (j.contains("username") ? j["username"] : "Guest");

    //make a call to validate if they're a guest || for now we don't, we assume till VPS is up

    return account;
	}

  }