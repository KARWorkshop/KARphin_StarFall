#pragma once

//defines a packet for when a new player joins

#include <SFML/Network/Packet.hpp>
#include <Core/NetPlayProto.h>

#include <Core/KAR/Netplay/WarpRelayUserAccount.hpp>
#include <Core/KAR/Versioning.hpp>

namespace Netplay::Packet
{
	//defines a packet for on player join data
	struct OnPlayerJoinPacket
	{
    WarpRelay::WarpRelayAccount account; //the account of the player

		uint8_t PID = 0;
	};

	//packages a player join packet
	static inline sf::Packet GeneratePacket_OnPlayerJoin(const OnPlayerJoinPacket& data)
	{
    sf::Packet p;
    p << (uint8_t)NetPlay::MessageID::PlayerJoin;

		p << data.PID;

		p << data.account.displayName;
    p << data.account.customIconURL;

		p << (uint8_t)data.account.rank;
    p << (uint8_t)data.account.region;
    p << (uint8_t)data.account.platform;

		return p;
  }

	//parses a player join packet
	static inline OnPlayerJoinPacket ParsePacket_OnPlayerJoin(sf::Packet& packet)
	{
    OnPlayerJoinPacket data;

		packet >> data.PID;

    packet >> data.account.displayName;
    packet >> data.account.customIconURL;

		uint8_t d = 0;
    packet >> d;
    data.account.rank = (WarpRelay::Rank)d;
    packet >> d;
    data.account.region = (WarpRelay::Region)d;
    packet >> d;
    data.account.platform = (WarpRelay::Platform)d;

    return data;
	}
  }