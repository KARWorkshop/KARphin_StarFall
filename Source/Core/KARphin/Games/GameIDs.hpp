#pragma once

//defines the game IDs we check around for

#include <string>

namespace KAR::GameIDs
{
static const int GAME_ID_VANNILA_COUNT = 4;

	//the base game IDs
static const char* GAME_ID_STRS_VANILLA[GAME_ID_VANNILA_COUNT] = {
  "GKYE01", //NA
	"GKYJ01", //JP
	"GKYP01", //PAL
  "GKYE01" //KOR
};

// gets backside game ID
static inline const char* GetGameID_Vanilla_NA()
{
  return GAME_ID_STRS_VANILLA[0];
}

//checks if it's a vanilla ID
static inline bool IsGameID_Vanilla(const char* gameID)
{
  for (int i = 0; i < GAME_ID_VANNILA_COUNT; ++i)
  {
    if (!strcmp(gameID, GAME_ID_STRS_VANILLA[i]))
      return true;
  }

  return false;
}

static const int GAME_ID_MODDED_GEN_1_COUNT = 2;

//the Backside 4 and Hack Pack IDs
static const char* GAME_ID_STRS_MODDED_GEN_1[GAME_ID_MODDED_GEN_1_COUNT] = {
    "KHPE01",  // Hack Pack
    "KBSE02"  // Backside 4
};

// gets backside game ID
static inline const char* GetGameID_Modded_Gen_1_Backside()
{
  return GAME_ID_STRS_MODDED_GEN_1[1];
}

// checks if it's a modded gen 1 ID
static inline bool IsGameID_Modded_Gen_1(const char* gameID)
{
  for (int i = 0; i < GAME_ID_MODDED_GEN_1_COUNT; ++i)
  {
    if (!strcmp(gameID, GAME_ID_STRS_MODDED_GEN_1[i]))
      return true;
  }

  return false;
}

static const int GAME_ID_MODDED_GEN_2_COUNT = 1;

//new generation Ignition ID
static const char* GAME_ID_STRS_MODDED_GEN_2[GAME_ID_MODDED_GEN_2_COUNT] = {
    "IGNE01" //Ignition
};

//gets ignition game ID
static inline const char* GetGameID_Modded_Gen_2_Ignition()
{
  return GAME_ID_STRS_MODDED_GEN_2[0];
}

// checks if it's a modded gen 2 ID
static inline bool IsGameID_Modded_Gen_2(const char* gameID)
{
  for (int i = 0; i < GAME_ID_MODDED_GEN_2_COUNT; ++i)
  {
    if (!strcmp(gameID, GAME_ID_STRS_MODDED_GEN_2[i]))
      return true;
  }

  return false;
}

}