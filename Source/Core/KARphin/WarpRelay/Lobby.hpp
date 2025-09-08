#pragma once

//defines a lobby

#include <string>

namespace KARphin::WarpRelay::Netplay
{
  //defines a lobby type
  enum class LobbyType
  {
    Public = 0, //the default state of a lobby
  };

	//defines a lobby
	struct Lobby
	{
    uint8_t ourPort = 0; //our port used to inject our auto code
    uint8_t playerCount = 0; //the total number of players that are in the match
    uint8_t playerIDs[4] = {0, 0, 0, 0}; //the player IDs given out by Dolphin
    std::string gameID = "",  // stores the game ID
        hostCode_IP = "",     // stores the host code/IP used to link to the lobby
        password = "",        // the password used to enter a lobby
        hostUsername = ""; //the user that was the host of the lobby
    std::string playerDisplayNames[4] = {"", "", "", ""}; //stores the player names
    std::string playerIconURLs[4] = {"", "", "", ""};  // stores the player urls

    //the properties of the lobby, theses need to be updated for all players if changed
    bool isTournyMode = false; //is tourny mode enabled or disabled
    bool isRanked = false; //is this lobby ranked or not

    //the static instance of the lobby
    static inline Lobby& Instance()
    {
      static Lobby l;
      return l;
    }
	};
}