#pragma once

//defines the spec and file format for the KAR Workshop Quick Install format

#include <string>

namespace KWQI
{
	//defines the struct containing the KWQI data
	struct KWQIData
	{
    bool usesMemoryCard = true,  // does this mod use a memory card
        useLuna = false;         // does this mod use the LUNA framework

    std::string versionMajor = "",  // the major version for the spec
        versionMinor = "",          // the minor version for the spec

       baseGame_ID = "",  // what game ID does it use as a base
        baseGame_Hash = "",  // what's the hash of the game

        gameID = "",         // the game ID for this mod
        geckoCodeURL = "",   // the gecko code URL for downloading
        memoryCardURL = "";  // the memory card URL for this mod if it uses it

	};
}