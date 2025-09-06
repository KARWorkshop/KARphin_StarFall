#pragma once

//defines the spec and file format for the KAR Workshop Quick Install format

#include <KARphin/IO/DirectoryStructure.hpp>
#include <KARphin/Games/GameIDs.hpp>

#include <Common/HttpRequest.h>

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

  //checks for a file with the game ID in the KWQI directory
  static inline bool CheckForKWQIFile(const std::string& gameID)
  {
    return (std::filesystem::exists(KAR::IO::GetDirectory_KWQI() + gameID + ".KWQI"));
  }

  //loads a file in the KWQI directory

  //checks for some default KWQI files we assume will be there, if not install them
  static inline void InstallDefaultKWQI()
  {
    if (!CheckForKWQIFile(KAR::GameIDs::GetGameID_Vanilla_NA())) //installs Deluxe (UP keeps it as the vanilla ID and it's annoying but WHATEVER
    {
      Common::HttpRequest http;

      // The server always redirects once to the same location.
      http.FollowRedirects(1);

      const Common::HttpRequest::Response response = http.Get("https://github.com/KARWorkshop/Patches/releases/download/Deluxe/GKYE01.KWQI");
      std::string FP = "";
      if (response.has_value())  // writes the image to cache
      {
        // packs data
        const std::vector<uint8_t> data = response.value();
        FP = KAR::IO::GetDirectory_KWQI() + "GKYE01.KWQI";
        File::CreateEmptyFile(FP);
        std::ofstream outFile(FP, std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
        outFile.close();
      }
    }

    if (!CheckForKWQIFile(KAR::GameIDs::GetGameID_Modded_Gen_1_Backside()))  // installs B4
    {
      Common::HttpRequest http;

      // The server always redirects once to the same location.
      http.FollowRedirects(1);

      const Common::HttpRequest::Response response =
          http.Get("https://github.com/KARWorkshop/Patches/releases/download/B4/KBSE02.KWQI");
      std::string FP = "";
      if (response.has_value())  // writes the image to cache
      {
        // packs data
        const std::vector<uint8_t> data = response.value();
        FP = KAR::IO::GetDirectory_KWQI() + "KBSE02.KWQI";
        File::CreateEmptyFile(FP);
        std::ofstream outFile(FP, std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
        outFile.close();
      }
    }

    if (!CheckForKWQIFile(KAR::GameIDs::GetGameID_Modded_Gen_2_Ignition()))  // installs Ignition
    {
      Common::HttpRequest http;

      // The server always redirects once to the same location.
      http.FollowRedirects(1);

      const Common::HttpRequest::Response response =
          http.Get("https://github.com/KARWorkshop/Patches/releases/download/Deluxe/GKYE01.KWQI");
      std::string FP = "";
      if (response.has_value())  // writes the image to cache
      {
        // packs data
        const std::vector<uint8_t> data = response.value();
        FP = KAR::IO::GetDirectory_KWQI() + "IGNE01.KWQI";
        File::CreateEmptyFile(FP);
        std::ofstream outFile(FP, std::ios::binary);
        outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
        outFile.close();
      }
    }

  }
  }