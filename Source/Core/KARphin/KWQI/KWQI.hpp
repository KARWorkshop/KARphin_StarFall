#pragma once

//defines the spec and file format for the KAR Workshop Quick Install format

#include <KARphin/IO/DirectoryStructure.hpp>
#include <KARphin/Games/GameIDs.hpp>

#include <KARphin/Vender/json_fwd.hpp>
#include <KARphin/Vender/json.hpp>

#include <Common/HttpRequest.h>

namespace KWQI
{
  //the spec version

  //defines the framework it uses
  enum class Framework
  {
    HackPack = 0, //a legacy support for B4

    Hoshi, //based on Deluxe
    Luna, //a fork of Hoshi that adds new features

    Count
  };

	//defines the struct containing the KWQI data
	struct KWQIData
	{
    Framework framework = Framework::Count; //the framework it uses

    std::string displayName = "",  // the name to show
        desc = "",                 // the description of the mod
        authors = "",              // who made it

        gameID = "", //the game ID for this mod

      baseReleaseURL = ""; //the base URL for where the release is located

    //writes a KWQI file
    inline void WriteToDisc()
    {
      const std::filesystem::path fp = KAR::IO::GetDirectory_KWQI() + gameID + ".game";
      if (std::filesystem::exists(fp))
        std::filesystem::remove(fp);

      nlohmann::json data;
      File::CreateEmptyFile(fp.string());
      File::WriteStringToFile(fp.string(), data.dump());
    }

    //loads a KWQI file

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
      KWQIData data;
      data.gameID = KAR::GameIDs::GetGameID_Vanilla_NA();


      Common::HttpRequest http;

      // The server always redirects once to the same location.
      http.FollowRedirects(1);

      const Common::HttpRequest::Response response = http.Get("https://github.com/KARWorkshop/Patches/releases/download/Deluxe/GKYE01.KWQI");
      std::string FP = "";
      if (response.has_value())  // writes the image to cache
      {
        // packs data
        std::istringstream ss(std::string(response->begin(), response->end()));
        FP = KAR::IO::GetDirectory_KWQI() + "GKYE01.KWQI";
        File::WriteStringToFile(FP, ss.str());
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
        std::istringstream ss(std::string(response->begin(), response->end()));
        FP = KAR::IO::GetDirectory_KWQI() + "KBSE02.KWQI";
        File::WriteStringToFile(FP, ss.str());
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
        std::istringstream ss(std::string(response->begin(), response->end()));
        FP = KAR::IO::GetDirectory_KWQI() + "IGNE01.KWQI";
        File::WriteStringToFile(FP, ss.str());
      }
    }

  }
  }