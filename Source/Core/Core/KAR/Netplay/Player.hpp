#pragma once

//defines a few types and structs for Players in the Lobby

#include <Core/NetPlayProto.h>

#include <deque>

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

		//uint8_t portIndex = 0; //we use this to adjust according based on the Player

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

	//groups players and spectators
	#define MAX_ACTIVE_NETPLAY_PLAYERS 4
	#define MAX_TOTAL_PLAYERS_IN_SERVER 255
	struct PlayerSpectatorGroupData
	{
    uint8_t totalPlayersInServer = 0; //we have a total amount just to stop the max connections, even if we will never see it

    std::deque<Player> players; //the active players assigned a port

		std::deque<Player> spectators;  // the spectators watching, this also accounts for TO Spectators

		//is the server capped at total players
    inline bool IsAtServerPlayerCap() const
    {
      return totalPlayersInServer == MAX_TOTAL_PLAYERS_IN_SERVER;
    }

		//is the active player cap reached
    inline bool IsAtActivePlayerCap() const
    {
			return players.size() == MAX_ACTIVE_NETPLAY_PLAYERS;
    }

		//adds a active player
    inline Player* AddActivePlayer(const Player& player)
		{
      if (IsAtActivePlayerCap())
        return nullptr;

			players.emplace_back(player);
      totalPlayersInServer++;
      return &players[players.size() - 1];
		}

		//removes a active player by PID
    inline void RemoveActivePlayer(const NetPlay::PlayerId pid)
    {
      for (size_t i = 0; i < players.size(); ++i)
      {
				if (players[i].pid == pid)
				{
          players.erase(players.begin() + i);
          return;
				}
      }
    }

		//gets a player by PID
		inline Player* GetActivePlayer(const NetPlay::PlayerId pid)
		{
      for (size_t i = 0; i < players.size(); ++i)
      {
        if (players[i].pid == pid)
          return &players[i];
      }

			return nullptr;
		}

		//gets the highest ping of all the active players
		inline uint32_t GetMaxPingOfActivePlayers() const
		{
			uint32_t ping = 0;

			for (size_t i = 0; i < players.size(); ++i)
			{
        if (players[i].ping > ping)
          ping = players[i].ping;
			}

			return ping;
		}
	};
}