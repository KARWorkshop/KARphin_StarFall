#pragma once

//defines functions for sending and parsing a connect packet

#include <SFML/Network/Packet.hpp>

#include <Core/KAR/Netplay/WarpRelayUserAccount.hpp>
#include <Core/KAR/Versioning.hpp>

namespace KAR::Netplay::Packet
{
	//defines a connect packet
	struct ConnectPacket
	{
    KAR::WarpRelay::Rank rank = KAR::WarpRelay::Rank::Count;
    KAR::WarpRelay::Region region = KAR::WarpRelay::Region::Count;

    std::string displayName = "",  // the name of the user to display

			//build data
			majorBuild = KAR_VERSION_MAJOR, minorBuild = KAR_VERSION_MINOR,
                hotfix = KAR_VERSION_HOT_FIX;
	};

	//generates a connect packet
	static inline sf::Packet GeneratePacket_Connect(const WarpRelay::WarpRelayAccount& account)
	{
    sf::Packet packet;

    packet << KAR_VERSION_MAJOR;
    packet << KAR_VERSION_MINOR;
    packet << KAR_VERSION_HOT_FIX;

		packet << account.displayName;

		packet << account.rank;
    packet << account.region;

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

    packet >> connect.rank;
    packet >> connect.region;

    return connect;
  }
  }