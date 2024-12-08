#pragma once

//defines data KARphin uses at Boot, also stores extra settings such as FS codes

#include <Core/KAR/json.hpp>

#include <Core/KAR/Mods/BuiltIn/FSCodes.hpp>
#include <Core/KAR/Versioning.hpp>

namespace KAR::Boot
{
  //defines what menu of KARphin we are booting into
  enum class KARphinBootState : uint8_t
  {
    Main = 0, //the default menu, no netplay or anything

    Host, //we boot into the host menu

    LobbyList, //we boot into the lobby list

    Count
  };

// defines the global settings we store
struct KARSettings
{
  //---general user

  KARphinBootState bootState = KARphinBootState::Main;  // are we booting into KARphin Netplay menus

  uint32_t warpRelayAccountIndex = 0; //the Warp Relay account index

  //---game settings

  Mod::BuiltIn::NA::FS::FullScreenCodeIndex FSCode =
      Mod::BuiltIn::NA::FS::FullScreenCodeIndex::Auto;  // what FS code are we using

  // are we booting into the main menu or the debug menu

  bool useDefaultAutoGenMemoryCard =
      true;  // are we using the default memory card or loading whatever is there

  std::string gameID = "";  // the Game ID we're injecting mods into
};

// writes it to disc
static inline void WriteKARSettingsToDisc(const KARSettings& settings)
{
  const std::string p = File::GetExeDirectory() + "/main.boot";
  File::CreateEmptyFile(p);

  nlohmann::json j;
  j["majorVer"] = KAR_VERSION_MAJOR;

  j["bootState"] = (uint8_t)settings.bootState;
  j["warpRelayAccount"] = settings.warpRelayAccountIndex;

  j["gameID"] = settings.gameID;

  j["fs"] = (uint8_t)settings.FSCode;
  j["useAutoGenMemCard"] = settings.useDefaultAutoGenMemoryCard;

  File::WriteStringToFile(p, j.dump());
}

// loads it from disc
static inline KARSettings LoadKARSettingsFromDisc(bool& error, std::string& errorMessage)
{
  KARSettings settings;
  const std::string p = File::GetExeDirectory() + "/main.boot";
  if (!File::Exists(p))
  {
    error = true;
    errorMessage = "No Boot Settings";
    return settings;
  }

  std::string d = "";
  File::ReadFileToString(p, d);
  nlohmann::json j = nlohmann::json::parse(d);

  // throw a error if versions conflict
  const std::string ver = (j.contains("majorVer") ? j["majorVer"] : "NOPE");
  if (ver != KAR_VERSION_MAJOR)
  {
    error = true;
    errorMessage =
        std::string("Version conflict, your version, \"" + std::string(KAR_VERSION_MAJOR) +
                    "\" is not the same as the one that made the file. \"" + ver + "\"");
    return settings;
  }

   settings.warpRelayAccountIndex =
      (j.contains("warpRelayAccount") ? j["warpRelayAccount"].get<uint32_t>() : 0);

   settings.bootState =
       (j.contains("bootState") ? (KARphinBootState)(j["bootState"].get<uint8_t>()) :
                                  KARphinBootState::Main);

  settings.gameID = (j.contains("gameID") ? j["gameID"] : "");

  settings.FSCode = (Mod::BuiltIn::NA::FS::FullScreenCodeIndex)(
      j.contains("fs") ? j["fs"].get<uint8_t>() : 0);
  settings.useDefaultAutoGenMemoryCard =
      (j.contains("useAutoGenMemCard") ? j["useAutoGenMemCard"].get<bool>() : true);

  return settings;
}
}