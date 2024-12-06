#include <Core/KAR/Netplay/WarpRelayUserAccount.hpp>

// stores all the Warp Relay accounts the user has locally
std::vector<WarpRelay::WarpRelayAccount> accounts;

// stores the currently loaded in account
WarpRelay::WarpRelayAccount* loggedInAccount = nullptr;
uint32_t accountIndex = 0;
