#pragma once

//defines a lobby

#include <string>

namespace KAR::Lobby
{
	//defines a lobby
	struct Lobby
	{
    uint8_t playerCount = 0; //the total number of players that are in the match
    std::string gameID = ""; //stores the game ID
    std::string playerDisplayNames[4] = {"", "", "", ""}; //stores the player names
    std::string playerIconURLs[4] = {"", "", "", ""};  // stores the player urls
	};
}