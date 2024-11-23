#pragma once

//defines a gecko code mod

#include <Common/FileUtil.h>

namespace KAR::Mod::ASM
{
	//permapath for built-in gecko codes
	static inline std::string GetPermaBuiltInGeckoCodePath()
	{
    return File::GetExeDirectory() + "/EmbededCodes/";
	}

	//defines a gecko code it bundles

	//defines a Gecko Code mod
	struct GeckoMod
	{
		//is it client side or server

		//name of the mod
		//description
		//creator

		//the total number of sub-codes it calls into
	};
}