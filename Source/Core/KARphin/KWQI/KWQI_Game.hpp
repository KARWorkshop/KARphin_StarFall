#pragma once

//defines the spec and file format for the KAR Workshop Quick Install format for full ISO games
//for spec see https://github.com/KARWorkshop/KAR-Wiki/blob/main/Specs/KWQI/Game.md

#include <KARphin/IO/DirectoryStructure.hpp>
#include <KARphin/Games/GameIDs.hpp>

#include <KARphin/Vender/json_fwd.hpp>
#include <KARphin/Vender/json.hpp>

#include <Common/HttpRequest.h>

namespace KWQI::Game
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

	//defines the struct containing the KWQI data for games
	struct KWQIData_Game
	{
    Framework framework = Framework::Count; //the framework it uses

    std::string displayName = "",  // the name to show
        desc = "",                 // the description of the mod
        authors = "",              // who made it

        gameID = "",  // the game ID for this mod

        memoryCardURL = "", //the url for the memory card for downloading
        geckoCodeURL = ""; //the url for the gecko code to download

    //writes a KWQI file
    inline void WriteToDisc()
    {
      const std::filesystem::path fp = KAR::IO::GetDirectory_KWQI() + gameID + ".game";
      if (std::filesystem::exists(fp))
        std::filesystem::remove(fp);

      nlohmann::json data;
      data["framework"] = (int)framework;

      data["displayName"] = displayName;
      data["desc"] = desc;

      data["gameID"] = gameID;

      data["memoryCardURL"] = memoryCardURL;
      data["geckoCodeURL"] = geckoCodeURL;

      File::CreateEmptyFile(fp.string());
      File::WriteStringToFile(fp.string(), data.dump());
    }

    //parse str into data
    inline void Parse(const std::string& data)
    {
      nlohmann::json kwqi = nlohmann::json::parse(data);
      if (kwqi.contains("framework")) { framework = (Framework)(kwqi["framework"].get<int>()); }
      if (kwqi.contains("displayName")) { displayName = kwqi["displayName"].get<std::string>(); }
      if (kwqi.contains("desc")) { desc = kwqi["desc"].get<std::string>(); }
      if (kwqi.contains("gameID")) { gameID = kwqi["gameID"].get<std::string>(); }
      if (kwqi.contains("memoryCardURL")) { memoryCardURL = kwqi["memoryCardURL"].get<std::string>(); }
      if (kwqi.contains("geckoCodeURL")) { geckoCodeURL = kwqi["geckoCodeURL"].get<std::string>(); }
    }
	};

  //returns a predefined KWQI data for Deluxe/Vanilla KAR
  static inline KWQIData_Game GetPredefinedKWQIGameData_Deluxe_VanillaNA()
  {
    KWQIData_Game data;
    data.displayName = "Deluxe - Vanilla NA KAR";
    data.desc = "A vanilla NA KAR or Deluxe, a new mod that changes the base of KAR, a refresh of "
                "the Hack Pack.";
    data.gameID = "GKYE01";
    data.authors = "HAL - Uncle Punch";

    data.framework = Framework::Hoshi;

    data.geckoCodeURL = "https://github.com/KARWorkshop/Patches/releases/download/Deluxe/GKYE01.ini";
    data.memoryCardURL = "https://github.com/KARWorkshop/Patches/releases/download/Deluxe/StandardRuleSet.USA.raw";

    return data;
  }

  //returns a predefined KWQI data for Backside 4
  static inline KWQIData_Game GetPredefinedKWQIGameData_Backside4()
  {
    KWQIData_Game data;
    data.displayName = "Backside 4";
    data.desc = "A remix of the Hack Pack, uses the legacy framework before Hoshi or Luna.";
    data.gameID = "KBSE02";
    data.authors = "Taco and the KAR Community";

    data.framework = Framework::HackPack;

    data.geckoCodeURL = "https://github.com/KARWorkshop/Patches/releases/download/B4/KBSE02.ini";
    data.memoryCardURL = "https://github.com/KARWorkshop/Patches/releases/download/Deluxe/StandardRuleSet.USA.raw";  // we just have Deluxe and Backside share the same memory card

    return data;
  }

  //returns a predefined KWQI data for Ignition
  static inline KWQIData_Game GetPredefinedKWQIGameData_Ignition()
  {
    KWQIData_Game data;
    data.displayName = "Ignition";
    data.desc = "A fork of Deluxe and Hoshi, adding tweaks for mods and expanded machines. Uses the Luna framework.";
    data.gameID = "IGNE01";
    data.authors = "Jas";

    data.framework = Framework::Luna;

    data.geckoCodeURL = "https://github.com/SeanMott/KAR-Ignition/releases/download/beta/IGNE01.ini";
    data.memoryCardURL = "https://github.com/KARWorkshop/Patches/releases/download/Deluxe/GKYE01.ini";

    return data;
  }

  //installs the default mods
  static inline void InstallDefaultMods()
  {
    GetPredefinedKWQIGameData_Ignition().WriteToDisc();
    GetPredefinedKWQIGameData_Backside4().WriteToDisc();
    GetPredefinedKWQIGameData_Deluxe_VanillaNA().WriteToDisc();
  }

  //checks for a file with the game ID in the KWQI directory
  static inline bool CheckForKWQIFile(const std::string& gameID)
  {
    return (std::filesystem::exists(KAR::IO::GetDirectory_KWQI() + gameID + ".game"));
  }

  //loads a file in the KWQI directory
  static inline KWQIData_Game LoadGameKWQIFile(const std::string& gameID)
  {
    std::string str = "";
    File::ReadFileToString(KAR::IO::GetDirectory_KWQI() + gameID + ".game", str);
    KWQIData_Game g;
    g.Parse(str);
    return g;
  }

 }