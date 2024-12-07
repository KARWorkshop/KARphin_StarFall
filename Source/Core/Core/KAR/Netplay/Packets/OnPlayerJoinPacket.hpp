#pragma once

//defines a packet for when a new player joins

#include <SFML/Network/Packet.hpp>
#include <Core/NetPlayProto.h>

#include <Core/KAR/Netplay/Packets/NetworkSerilizeAccount.hpp>
#include <Core/KAR/Netplay/WarpRelayUserAccount.hpp>
#include <Core/KAR/Versioning.hpp>

namespace Netplay::Packet
{
	//defines a packet for on player join data
	struct OnPlayerJoinPacket
	{
    uint8_t PID = 0;

    WarpRelay::WarpRelayAccount account; //the account of the player
	};

	//packages a player join packet
	static inline sf::Packet GeneratePacket_OnPlayerJoin(const OnPlayerJoinPacket& data)
	{
    sf::Packet p;
    p << (uint8_t)NetPlay::MessageID::PlayerJoin;

		p << data.PID;

		Serilize::SerilizeIntoPacket_AccountData(&data.account, p);

		return p;
  }

	//parses a player join packet
	static inline OnPlayerJoinPacket ParsePacket_OnPlayerJoin(sf::Packet& packet)
	{
    OnPlayerJoinPacket data;

		packet >> data.PID;

   Serilize::DeserilizeFromPacket_AccountData(&data.account, packet);

    return data;
	}
  }