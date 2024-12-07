#pragma once

//all the functions for getting various directories and such for mods

#include <Common/FileUtil.h>

namespace KAR::Mod::IO
{
// permapath for built-in gecko codes
static inline std::string GetPermaBuiltInGeckoCodePath()
{
  return File::GetExeDirectory() + "/Sys/EmbededCodes/";
}

// gets the mods directory
inline std::string GetModsDirectory()
{
  const std::string modsDir = File::GetExeDirectory() + "/../Mods";
  if (!File::Exists(modsDir))
    File::CreateDir(modsDir);

  return modsDir;
}

}