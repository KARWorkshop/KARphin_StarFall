#pragma once

//defines a few types and structs for Players in the Lobby

#include <Core/NetPlayProto.h>

namespace Netplay::Core
{
	//defines the kinds of Players
	enum class PlayerType
	{
		Player = 0, //are they actually partaking in the match and sending inputs

		Spectator, //are they just spectating

		Spectator_TO, //are they just spectating but also a TO

		Count
	};

	//defines a player in the Lobby
	struct Player
	{
    NetPlay::PlayerId pid{}; //the unique network ID
    u32 ping = 0; //the ping of the player

		PlayerType type = PlayerType::Count;  // are they a Player or a Spectator

		std::string displayName = "",  // the display name of this Player
        customIconURL = ""; //the custom icon URL for this Player

		//is this player the host of the match
    inline bool IsHost() const { return pid == 1; }

		//is the player a Player
    inline bool IsPlayer() const { return type == PlayerType::Player; }

		//is the player a Spectator
    inline bool IsSpectator() const { return type == PlayerType::Spectator; }

		//is the player a Spectator TO
    inline bool IsSpectatorTO() const { return type == PlayerType::Spectator_TO; }
	};
}