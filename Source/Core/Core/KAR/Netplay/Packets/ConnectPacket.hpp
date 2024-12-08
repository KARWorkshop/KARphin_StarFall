#pragma once

//defines functions for sending and parsing a connect packet

#include <SFML/Network/Packet.hpp>

#include <Core/KAR/WarpRelay/WarpRelayAccountManager.hpp>
#include <Core/KAR/Versioning.hpp>

namespace KAR::Netplay::Packet
{
	//defines a connect packet
	struct ConnectPacket
	{
    KAR::WarpRelay::Rank rank = KAR::WarpRelay::Rank::Count;
    KAR::WarpRelay::Region region = KAR::WarpRelay::Region::Count;

    std::string displayName = "",  // the name of the user to display
    customIconURL = "", //defines the URL for a custom URL icon, only useable by non-guest accounts

			//build data
			majorBuild = KAR_VERSION_MAJOR, minorBuild = KAR_VERSION_MINOR,
                hotfix = KAR_VERSION_HOT_FIX;
	};

	//generates a connect packet
  static inline sf::Packet GeneratePacket_Connect(const ConnectPacket& data)
	{
    sf::Packet packet;

    packet << data.majorBuild;
    packet << data.minorBuild;
    packet << data.hotfix;

		packet << data.displayName;
    packet << data.customIconURL;

		packet << (uint8_t)data.rank;
    packet << (uint8_t)data.region;

		return packet;
	}

	//parses a connect packet
  static inline ConnectPacket ParsePacket_Connect(sf::Packet& packet)
  {
    ConnectPacket connect;

    packet >> connect.majorBuild;
    packet >> connect.minorBuild;
    packet >> connect.hotfix;

    packet >> connect.displayName;
    packet >> connect.customIconURL;

    uint8_t d = 0;
    packet >> d;
    connect.rank = (WarpRelay::Rank)d;
    packet >> d;
    connect.region = (WarpRelay::Region)d;

    return connect;
  }
  }