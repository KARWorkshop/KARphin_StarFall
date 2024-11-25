#pragma once

// defines a settings file for built-in mods and their tweaks

#include <Core/KAR/json.hpp>

#include <Core/KAR/Mods/BuiltIn/FSCodes.hpp>
#include <Core/KAR/Versioning.hpp>

namespace KAR::Mod::BuiltIn
{
// defines the global settings we store
struct KARSettings
{
  BuiltIn::NA::FS::FullScreenCodeIndex FSCode =
      BuiltIn::NA::FS::FullScreenCodeIndex::None;  // what FS code are we using

  // are we booting into the main menu or the debug menu

  bool useDefaultAutoGenMemoryCard =
      true;  // are we using the default memory card or loading whatever is there

  std::string gameID = "";  // the Game ID we're injecting mods into
};

// writes it to disc
static inline void WriteKARBuiltInModSettingsToDisc(const KARSettings& settings)
{
  const std::string p = File::GetExeDirectory() + "/BuiltIn_NA.karmod";
  File::CreateEmptyFile(p);

  nlohmann::json j;
  j["majorVer"] = KAR_VERSION_MAJOR;

  j["gameID"] = settings.gameID;

  j["fs"] = (uint8_t)settings.FSCode;
  j["useAutoGenMemCard"] = settings.useDefaultAutoGenMemoryCard;

  File::WriteStringToFile(p, j.dump());
}

// loads it from disc
static inline KARSettings LoadKARBuiltInModSettingsFromDisc(bool& error, std::string& errorMessage)
{
  KARSettings settings;
  const std::string p = File::GetExeDirectory() + "/BuiltIn_NA.karmod";
  if (!File::Exists(p))
  {
    error = true;
    errorMessage = "No built-in Mod file";
    return settings;
  }

  std::string d = "";
  File::ReadFileToString(p, d);
  nlohmann::json j = nlohmann::json::parse(d);

  //throw a error if versions conflict
  const std::string ver = j["majorVer"];
  if (ver != KAR_VERSION_MAJOR)
  {
    error = true;
    errorMessage = std::string("Version conflict, your version, \"" + std::string(KAR_VERSION_MAJOR) + "\" is not the same as the one that made the file. \"" +
      ver + "\"");
    return settings;
  }

  settings.gameID = j["gameID"];

  settings.FSCode = (NA::FS::FullScreenCodeIndex)j["fs"];
  settings.useDefaultAutoGenMemoryCard = j["useAutoGenMemCard"];

  return settings;
}

// defines the local settings per-ROM
}  // namespace KAR::Mods