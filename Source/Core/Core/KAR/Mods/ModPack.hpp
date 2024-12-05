#pragma once

//defines a mod pack

#include <Core/KAR/json.hpp>

namespace KAR::Mod::Pack
{
	//defines the kinds of mods
	enum class ModType
	{
		GeckoCode = 0x00, //defines a gecko code mod
	};

	//defines a manifest file
	struct Manifest
	{
    std::vector<std::string> authors; //the authors

    std::string name = "",  // name of the mod
        shortDesc = "",     // the short descrption used on tooltips
        longDesc = "",      // the long description used on info

        version = "",  // the version of the build currently
        repo = "";     // the repo this mod pack came from
	};

	//defines a mod pack
	struct ModPack
	{

	};
}