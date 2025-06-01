#pragma once

// defines a common header file for managing loading the desired gecko code mods

#include <KARphin/IO/DirectoryStructure.hpp>

#include "Common/IniFile.h"

#include "Core/ConfigManager.h"
#include "Core/GeckoCode.h"
#include "Core/GeckoCodeConfig.h"

namespace KAR::Mods::Codes
{
// gets the path to the gecko codes
static inline std::string GetGeckoCodeFilePath(const std::string& gameID)
{
  return KAR::IO::GetDirectory_GeckoCodes() + DIR_SEP + gameID + ".ini";
}

// loads all server side gecko codes
static inline std::vector<Gecko::GeckoCode> LoadGeckoCodes(const std::string& gameID)
{
  Common::IniFile codes, dummy = Common::IniFile();
  codes.Load(GetGeckoCodeFilePath(gameID));
  return Gecko::LoadCodes(codes, dummy);
}

// saves gecko codes to a file
static inline void SaveGeckoCodes(const std::filesystem::path& codeFP,
                                  const std::vector<Gecko::GeckoCode>& codes)
{
  if (codes.size() == 0)  // don't save if no codes
    return;

  Common::IniFile game_ini_local;
  game_ini_local.Load(codeFP.string());
  Gecko::SaveCodes(game_ini_local, codes);
  game_ini_local.Save(codeFP.string());
}

}  // namespace KAR::Mods::Codes