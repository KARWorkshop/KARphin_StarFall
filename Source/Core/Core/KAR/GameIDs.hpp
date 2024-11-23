#pragma once

//stores various game IDs

#include <string>

namespace KAR::GameData
{
	//NA game ID
static inline std::string GetGameID_NA()
{
  return "GKEY01";
}

	//PAL game ID
	//JP game ID

	//Hack Pack ID
static inline std::string GetGameID_HP()
{
  return "KHPE01";
}

	//Backside 2
static inline std::string GetGameID_BS()
{
  return "KBSE01";
}

	//backside 3

	//ignition

	//constellation

	//if it's NA and or modded
static inline bool IsNA_OrModdedVariant(const std::string& gameID)
{
  return (gameID == GetGameID_NA() || gameID == GetGameID_HP() || gameID == GetGameID_BS());
}
}