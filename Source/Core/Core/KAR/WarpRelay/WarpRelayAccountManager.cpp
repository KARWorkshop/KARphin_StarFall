#include <Core/KAR/WarpRelay/WarpRelayAccountManager.hpp>

// the accounts
std::vector<KAR::WarpRelay::WarpRelayAccount> accounts;

// the currently logged in account
KAR::WarpRelay::WarpRelayAccount* loggedInAccount;
uint32_t currentlyLoggedInAccountIndex;

// the downloaded custom icons, maps a URL to a FP of image
std::map<std::string, std::string> iconFPs;
