#pragma once

//defines functions for sending and parsing a connect packet

#include <SFML/Network/Packet.hpp>

#include <Core/KAR/Netplay/Packets/NetworkSerilizeAccount.hpp>
#include <Core/KAR/Netplay/WarpRelayUserAccount.hpp>
#include <Core/KAR/Versioning.hpp>

namespace Netplay::Packet
{
// defines a connect packet
struct ConnectPacket
{
  //account data
  WarpRelay::WarpRelayAccount account;

      // build data
      std::string majorBuild = KAR_VERSION_MAJOR, minorBuild = KAR_VERSION_MINOR, hotfix = KAR_VERSION_HOT_FIX;
};

  //generate a connect packet
  static inline sf::Packet GeneratePacket_Connect(const WarpRelay::WarpRelayAccount account)
  {
    sf::Packet packet;

    //send over the build data
    packet << KAR_VERSION_MAJOR;
    packet << KAR_VERSION_MINOR;
    packet << KAR_VERSION_HOT_FIX;

    Serilize::SerilizeIntoPacket_AccountData(&account, packet);

    return packet;
  }

  // parses a connect packet into a account
  static inline ConnectPacket ParsePacket_Connect(sf::Packet& packet)
  {
    ConnectPacket connect;

    packet >> connect.majorBuild;
    packet >> connect.minorBuild;
    packet >> connect.hotfix;

    Serilize::DeserilizeFromPacket_AccountData(&connect.account, packet);

    return connect;
  }

  }