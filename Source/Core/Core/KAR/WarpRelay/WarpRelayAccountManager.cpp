#include <Core/KAR/WarpRelay/WarpRelayAccountManager.hpp>

// the accounts
std::vector<KAR::WarpRelay::WarpRelayAccount> KAR::WarpRelay::WarpRelayAccountManager::accounts;

// the currently logged in account
KAR::WarpRelay::WarpRelayAccount* KAR::WarpRelay::WarpRelayAccountManager::loggedInAccount = nullptr;
uint32_t KAR::WarpRelay::WarpRelayAccountManager::currentlyLoggedInAccountIndex = 0;
