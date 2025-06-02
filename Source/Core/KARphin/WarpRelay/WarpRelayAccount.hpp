#pragma once

//defines a warp relay account

#include <string>

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
    static inline Account Instance()
    {
      static Account a;
      return a;
    }
  };
}  // namespace KAR::Account