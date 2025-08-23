#pragma once

//defines a warp relay account

#include <string>

#include <KARphin/IO/DirectoryStructure.hpp>
#include <Common/FileUtil.h>

#include "Core/Config/NetplaySettings.h"

#include <Common/IniFile.h>

namespace KAR::Account
{
  //defines a account instanced
  struct Account
  {
    uint8_t playerID = 0; //the player ID provided by Dolphin's network
    std::string displayName = "", //the display name we are using
      iconURL = ""; //the URL to the icon for downloading and rendering in the Lobby

    //is the account currently loaded
    inline bool IsValidAccount() { return (playerID != 0); }


    //returns the instance of the account
    static inline Account& Instance()
    {
      static Account a;
      return a;
    }

    //loads a file from disc
    inline void Load(const std::string& filepath)
    {
      Common::IniFile settings;
      settings.Load(filepath);
      Common::IniFile::Section* section = settings.GetOrCreateSection("Warp Relay");
      section->Get("displayName", &displayName);
      iconURL = section->Get("icon", &iconURL);
    }

    //writes data to a disc
    inline void Write(const std::string& filepath)
    {
      if (File::Exists(filepath))
        File::Delete(filepath, File::IfAbsentBehavior::NoConsoleWarning);

      File::CreateEmptyFile(filepath);

      Common::IniFile data;
      Common::IniFile::Section* section = data.GetOrCreateSection("Warp Relay");
      section->Set("displayName", displayName);
      section->Set("icon", iconURL);

      data.Save(filepath);
    }

  };

  //loads the default guest account
  static inline Account LoadAccount_Default()
  {
    const std::string accountDir = KAR::IO::GetDirectory_Account();
    const std::string guestFP = accountDir + "Guest.wr";

    Account acc;

    if (!File::Exists(guestFP))
    {
      acc.displayName = "Kirby";
      acc.iconURL = "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/"
                    "data-account/kirb_0.png";
      acc.Write(guestFP);
    }
    else
    {
      acc.Load(guestFP);
    }

    return acc;

  }

}  // namespace KAR::Account