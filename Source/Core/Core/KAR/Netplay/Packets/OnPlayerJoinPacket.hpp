#pragma once

//defines a packet for when a new player joins

#include <SFML/Network/Packet.hpp>
#include <Core/NetPlayProto.h>

#include <Core/KAR/WarpRelay/WarpRelayAccountManager.hpp>
#include <Core/KAR/Versioning.hpp>

namespace KAR::Netplay::Packet
{
	//defines a packet for on player join data
	struct OnPlayerJoinPacket
	{
    WarpRelay::Rank rank = WarpRelay::Rank::StarDust;
    WarpRelay::Region region = WarpRelay::Region::NA;

		uint8_t PID = 0;

    std::string displayName = "";
	};

	//packages a player join packet
	static inline sf::Packet GeneratePacket_OnPlayerJoin(const OnPlayerJoinPacket& data)
	{
    sf::Packet p;
    p << (uint8_t)NetPlay::MessageID::PlayerJoin;

		p << data.displayName;

		p << (uint8_t)data.rank;
    p << (uint8_t)data.region;

		p << data.PID;

		return p;
  }

	//parses a player join packet
	static inline OnPlayerJoinPacket ParsePacket_OnPlayerJoin(sf::Packet& packet)
	{
    OnPlayerJoinPacket data;

		packet >> data.displayName;

		uint8_t d = 0;
    packet >> d;
    data.rank = (WarpRelay::Rank)d;
    packet >> d;
    data.region = (WarpRelay::Region)d;

		packet >> data.PID;

    return data;
	}
  }