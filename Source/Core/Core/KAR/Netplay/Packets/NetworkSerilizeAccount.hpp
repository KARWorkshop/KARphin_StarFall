#pragma once

//functions for serilizing and deserilizing account data on the network

#include <SFML/Network/Packet.hpp>
#include <Core/NetPlayProto.h>

#include <Core/KAR/Netplay/WarpRelayUserAccount.hpp>

namespace Netplay::Packet::Serilize
{
// serilizes KAR account into the packet
static inline void SerilizeIntoPacket_AccountData(const WarpRelay::WarpRelayAccount* account,
                                                  sf::Packet& p)
{
  p << account->isGuestAccount;
 // p << (uint8_t)account->platform;
 // p << (uint8_t)account->region;
 // p << (uint8_t)account->rank;
  p << account->displayName;
}

// deserilizes KAR account from a packet
static inline void DeserilizeFromPacket_AccountData(WarpRelay::WarpRelayAccount* account,
                                                    sf::Packet& p)
{
  p >> account->isGuestAccount;
 // uint8_t data = 0;
 // p >> data;
 // account->platform = (WarpRelay::Platform)data;
 // p >> data;
 // account->region = (WarpRelay::Region)data;
 // p >> data;
 // account->rank = (WarpRelay::Rank)data;
  p >> account->displayName;
}
}  // namespace Netplay::Packet::Serilize