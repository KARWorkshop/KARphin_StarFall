#pragma once

//when a player connects we send a packet

#include <SFML/Network/Packet.hpp>

#include <string>

namespace KARphin::WarpRelay::Netplay::Packet
{
	//defines the player kind for joining
	enum class JoinKind
	{
		Player = 0x00, //they're a player and should be given a port for sending input
		Spectator, //they're a spectator and should not be given a port
		Bot, //they're a bot and should be given a port but will not be treated like a Player

		Count
	};

	//defines a on player connect packet
	struct Packet_OnPlayerConnect
	{
    JoinKind kind = JoinKind::Player; //what kind of join are they

    std::string clientVersion = ""; //the version of their client, if they got a incompatable version, reject them
    std::string nickname = ""; //the nickname they choose to show online
    std::string warpRelayIconURL = ""; //the URL for their warp relay icon
	};

	//packs data into a packet we can send accros the network
	static inline sf::Packet PackageDataIntoSFMLPacket_OnPlayerConnect(const Packet_OnPlayerConnect& data)
	{
    sf::Packet packet;

		return packet;
	}

	//unpacks the recived pack into our custom data struct
  static inline Packet_OnPlayerConnect UnpackSFMLPacket_OnPlayerConnect(const sf::Packet& packet)
  {
    Packet_OnPlayerConnect data;

    return data;
  }
}