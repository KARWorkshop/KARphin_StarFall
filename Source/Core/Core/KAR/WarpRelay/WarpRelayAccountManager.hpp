#pragma once

//defines a manager for the Warp Relay Accounts

#include <Core/KAR/WarpRelay/WarpRelayUserAccount.hpp>

namespace KAR::WarpRelay
{
struct WarpRelayAccountManager
{
  // the accounts
  static std::vector<WarpRelayAccount> accounts;

  // the currently logged in account
  static WarpRelayAccount* loggedInAccount;
  static uint32_t currentlyLoggedInAccountIndex;

  // gets all Account files and loads them
  static inline void LoadAllAccounts()
  {
    size_t count = accounts.size();
    accounts.clear();
    accounts.reserve(count);

    //load all files
    const std::vector<std::string> FPs = GetAllAccountFiles();
    count = FPs.size();
    for (size_t i = 0; i < count; ++i)
      accounts.emplace_back(LoadWarpRelayAccount(FPs[i]));

    //if none are found we generate a Guest Account
    if (!count)
      accounts.emplace_back(WarpRelayAccount());
  }

  // sets the currently logged in account
  static inline WarpRelayAccount* SetLoggedInAccount(uint32_t index)
  {
    const size_t accountCount = accounts.size();
    if (!accountCount) //generates a guest account
      accounts.emplace_back(WarpRelayAccount());

    //if the index doesn't match
    const size_t accountLastIndex = (!accountCount ? 0 : accountCount - 1);
    if (index > accountLastIndex)
      currentlyLoggedInAccountIndex = accountLastIndex;
    else
      currentlyLoggedInAccountIndex = index;

    loggedInAccount = &accounts[currentlyLoggedInAccountIndex];
    return loggedInAccount;
  }

  // logs out of the currently logged account || forces into Guest mode
  static inline void LogOutAccount()
  {
    loggedInAccount = nullptr;

    //gets the guest account if it exists
    for (size_t i = 0; i < accounts.size(); ++i)
    {
      if (accounts[i].isGuestAccount)
      {
        loggedInAccount = &accounts[i];
        currentlyLoggedInAccountIndex = i;
        break;
      }
    }

    //if it doesn't exist, generate a guest account
    if (!loggedInAccount)
    {
      accounts.emplace_back(WarpRelayAccount());
      currentlyLoggedInAccountIndex = 0;
      loggedInAccount = &accounts[0];
    }
  }

  // gets the currently logged in account
  static inline WarpRelayAccount* GetLoggedInAccount()
  {
    //if the logged in account is NULL, we log out, so we generate a guest account
    if (!loggedInAccount)
      LogOutAccount();

    return loggedInAccount;
  }
};
}