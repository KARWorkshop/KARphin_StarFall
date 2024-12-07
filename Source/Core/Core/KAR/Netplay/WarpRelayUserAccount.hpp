#pragma once

//defines data about the Warp Relay user on this system

#include <Core/KAR/json.hpp>

#include <Common/FileUtil.h>
#include "Common/FileSearch.h"

namespace WarpRelay
{
#define WARP_RELAY_USER_ACCOUNT_API_VERSION "1.0.0"

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

  //defines the platform
  enum class Platform : uint8_t
  {
    Windows = 0x00,
    Mac,
    Linux_SteamDeck,

    Switch,

    Count
  };

	//defines the data loaded from a warp relay file
	struct WarpRelayAccount
	{
    bool isGuestAccount = true; //guest accounts don't get paid sub-features

    Rank rank = Rank::StarDust; //defines the temp latter rank of the user
    Region region = Region::NA;  // the geo-region to use

    Platform platform = Platform::Windows;  // the platform this data was loaded on

    std::string displayName = "Kirby",  // the display name used online
      customIconURL = "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/data-account/Guest_Icon_NULL1.png",  // the URL/local path to the custom icon if they have one

        discordAccountLinkHash = "",  // the hash we use to validate they have a linked discord account
        googleAccountLinkHash = "",// the hash we use to validate they have a linked google account
        warpRelayAccountHash = "";  // the hash we use to validate they have a Warp Relay account and aren't just a guest
	};

  // returns the path to the folder containing all the Warp Relay Accounts
  static inline std::string GetAccountsDir()
  {
    const std::string dir = File::GetExeDirectory() + "/../Accounts/";
    if (!File::Exists(dir))
      File::CreateDir(dir);

    return dir;
  }

  // returns the file extention for a warp relay account file
  static inline std::string GetWarpRelayAccountFileExtension()
  {
    return ".wra";
  }

  //writes it to disc
  static inline void WriteWarpRelayAccount(const WarpRelayAccount& account)
  {
    const std::string accountPath = GetAccountsDir() + (account.warpRelayAccountHash == "" ? "Guest" : account.warpRelayAccountHash) + GetWarpRelayAccountFileExtension();

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
      return WarpRelayAccount(); //return a NULL file here

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
    account.isGuestAccount = (account.warpRelayAccountHash == "");

    return account;
	}

  // gets all the accounts folders
  static inline std::vector<std::string> GetAllAccountFiles()
  {
    return Common::DoFileSearch({GetAccountsDir()}, {GetWarpRelayAccountFileExtension()});
  }

  // stores all the Warp Relay accounts the user has locally
  static std::vector<WarpRelayAccount> accounts;

   // stores the currently loaded in account
  static WarpRelayAccount* loggedInAccount;
  static uint32_t accountIndex;

  //sets the logged in account
  static inline bool SetLoggedInAccount(const uint32_t index)
  {
    //fail if we have no accounts
    const size_t count = accounts.size();
    if (!count)
      return false;

    //sets the index, if we need to, fall back to a latest account in case our index is out of range
    const size_t lastIndex = (count == 1 ? 0 : static_cast<uint32_t>(count) - 1); //do a quick check for underflow
    accountIndex = (index > lastIndex ? lastIndex : index);
    loggedInAccount = &accounts[accountIndex];
    return true;
  }

  //gets the currently logged in account || if nothing is found, we generate a guest account
  static inline WarpRelayAccount* GetLoggedInAccount()
  {
    if (!loggedInAccount)
    {
      //attempt to relog in the user
      if (!SetLoggedInAccount(accountIndex))
      {
        //generates a Guest account
        accounts.resize(1, WarpRelayAccount());
        SetLoggedInAccount(0);
      }
    }

    return loggedInAccount;
  }

  //loads all the accounts, if none are found, force create a default account
  static inline bool LoadAllAccounts()
  {
    const std::vector<std::string> accFiles = GetAllAccountFiles();
    const size_t count = accFiles.size();
    accounts.clear();

    //if none are found we force a default guest account
    if (!count)
    {
      accounts.resize(1, WarpRelayAccount());
      return false;
    }

    //load the accounts
    accounts.resize(count);
    for (size_t i = 0; i < count; ++i)
      accounts[i] = LoadWarpRelayAccount(accFiles[i]);

    return true;
  }

  }