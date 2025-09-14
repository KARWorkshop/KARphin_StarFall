#pragma once

//defines a warp relay account

#include <KARphin/WarpRelay/Account/BannerLoader.hpp>
#include <KARphin/WarpRelay/Account/BannerIDMapper.hpp>

#include <string>

#include <KARphin/IO/DirectoryStructure.hpp>
#include <Common/FileUtil.h>

#include "Core/Config/NetplaySettings.h"

#include <KARphin/Vender/json.hpp>

namespace KAR::Account
{
  //defines a account instanced
  struct Account
  {
    uint8_t playerID = 0; //the player ID provided by Dolphin's network
    std::string displayName = "";  // the display name we are using
    std::string bannerURL = ""; //the URL for the banner we are using

    //is the account currently loaded
    inline bool IsValidAccount() { return (playerID != 0); }

    //returns the instance of the account
    static inline Account& Instance()
    {
      static Account a;
      return a;
    }

    //gets a default settings
    static inline Account DefaultSettings()
    {
      Account acc;
      acc.displayName = "Kirby";
      acc.bannerURL = KARphin::WarpRelay::Account::Banner::BANNER_URLS[0];
      return acc;
    }

    //gets default filepath
    static inline std::string DefaultFilepath()
    {
      return KAR::IO::GetDirectory_Account() + "guest.wrv2";
    }

    //loads a file from disc
    inline void Load(const std::string& filepath)
    {
      if (!std::filesystem::exists(filepath))
      {
        Account acc = DefaultSettings();
        displayName = acc.displayName;
        acc.bannerURL = KARphin::WarpRelay::Account::Banner::BANNER_URLS[0];
        acc.Write(filepath);
        return;
      }

      std::ifstream netInfoReader(filepath, std::ios::binary);
      std::vector<std::uint8_t> data((std::istreambuf_iterator<char>(netInfoReader)),
                                          std::istreambuf_iterator<char>());

      //if there's no data, use the default
      if (!data.size())
      {
        Account acc = DefaultSettings();
        displayName = acc.displayName;
        acc.bannerURL = KARphin::WarpRelay::Account::Banner::BANNER_URLS[0];
      }
      else // if it's the new format
      {
        nlohmann::json info = nlohmann::json::from_ubjson(data);
        if (info.contains("name")) { displayName = info["name"].get<std::string>(); }
        if (info.contains("bannerURL")) { bannerURL = info["bannerURL"].get<std::string>(); }
      }
    }

    //writes data to a disc
    inline void Write(const std::string& filepath)
    {
      nlohmann::json info;
      info["name"] = displayName;
      info["bannerURL"] = bannerURL;
      std::vector<std::uint8_t> data = nlohmann::json::to_ubjson(info);

      if (std::filesystem::exists(filepath))
        std::filesystem::remove(filepath);
      File::CreateEmptyFile(filepath);
      std::ofstream outFile(filepath, std::ios::binary);
      outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
      outFile.close();
    }

  };

  //loads the default Warp Relay Account
  static inline Account LoadDefaultWarpRelayAccount()
  {
    // deletes the "Accounts" folder since that was a error in the release to have alongside the
    // Account folder
    if (std::filesystem::exists(File::GetExeDirectory() + DIR_SEP + "Accounts"))
      std::filesystem::remove(File::GetExeDirectory() + DIR_SEP + "Accounts");

    //deletes the old format of warp relay data
    if (std::filesystem::exists(KAR::IO::GetDirectory_Account() + "guest.wr"))
      std::filesystem::remove(KAR::IO::GetDirectory_Account() + "guest.wr");
    if (std::filesystem::exists(KAR::IO::GetDirectory_Account() + "Guest.wr"))
      std::filesystem::remove(KAR::IO::GetDirectory_Account() + "Guest.wr");

    Account acc;
    acc.Load(Account::DefaultFilepath());
    return acc;
  }

}  // namespace KAR::Account