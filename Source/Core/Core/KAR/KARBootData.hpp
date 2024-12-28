#pragma once

//defines data KARphin uses at Boot, also stores extra settings such as FS codes

#include <Core/KAR/json.hpp>

#include <Core/KAR/Mods/BuiltIn/FSCodes.hpp>
#include <Core/KAR/Versioning.hpp>

namespace KAR::Boot
{
  //defines the update mode
  enum class UpdateMode : uint8_t
  {
    NoUpdate = 0, //we don't update
    AutoUpdate, //we are auto updating
    AutoUpdate_Dev, //we are auto updating on the dev build

    Count
  };

// defines the global settings we store
struct KARSettings
{
  //---general user

  uint32_t warpRelayAccountIndex = 0; //the Warp Relay account index
  UpdateMode updateMode = UpdateMode::AutoUpdate; //auto update

  bool hasSeenChangeLog = false; //have we seen the change log

  //---game settings

  Mod::BuiltIn::NA::FS::FullScreenCodeIndex FSCode =
      Mod::BuiltIn::NA::FS::FullScreenCodeIndex::Auto;  // what FS code are we using

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

  j["updateMode"] = (uint8_t)settings.updateMode;
  j["warpRelayAccount"] = settings.warpRelayAccountIndex;
  j["hasSeenChangeLog"] = settings.hasSeenChangeLog;

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

  settings.updateMode = (UpdateMode)(j.contains("updateMode") ? j["updateMode"].get<uint8_t>() : 1);
   settings.warpRelayAccountIndex =
      (j.contains("warpRelayAccount") ? j["warpRelayAccount"].get<uint32_t>() : 0);
  settings.hasSeenChangeLog =
      (j.contains("hasSeenChangeLog") ? j["hasSeenChangeLog"].get<bool>() : false);

  settings.gameID = (j.contains("gameID") ? j["gameID"] : "");

  settings.FSCode = (Mod::BuiltIn::NA::FS::FullScreenCodeIndex)(
      j.contains("fs") ? j["fs"].get<uint8_t>() : 0);
  settings.useDefaultAutoGenMemoryCard =
      (j.contains("useAutoGenMemCard") ? j["useAutoGenMemCard"].get<bool>() : true);

  return settings;
}
}