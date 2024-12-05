#pragma once

//defines handling packs of mods and loading them

#include <Core/KAR/Mods/ModPack.hpp>

#include <algorithm>
#include <memory>

//#include <mz_compat.h>
//#include <mz_os.h>

#include "Common/CommonPaths.h"
#include "Common/FileSearch.h"
#include "Common/FileUtil.h"
#include "Common/IOFile.h"
//#include "Common/MinizipUtil.h"
#include "Common/ScopeGuard.h"
#include "Common/StringUtil.h"

namespace KAR::Mod::Pack
{
	//gets the mods directory
	inline std::string GetModsDirectory()
	{
    const std::string modsDir = File::GetExeDirectory() + "/../Mods";
    if (!File::Exists(modsDir))
      File::CreateDir(modsDir);

		return modsDir;
	}

	static std::vector<ModPack> mods;

	//loads all mods
	inline bool LoadMods()
	{
		//gets the packs
   // const std::vector<std::string> pack_list = Common::DoFileSearch({GetModsDirectory()}, {".zip"});

		//checks for manifests

		//updates the mods

		return true;
	}

  }