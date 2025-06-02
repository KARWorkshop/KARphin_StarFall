#pragma once

//defines versioning info for KARphin

#include <string>

#define KARPHIN_VERSION_MAJOR "4"
#define KARPHIN_VERSION_MINOR "0"
#define KARPHIN_VERSION_HOTFIX "0"

namespace KAR
{
	//returns a version string
static inline std::string GetVersionStr_Maj_Min()
{
  return std::string(KARPHIN_VERSION_MAJOR) + "_" + KARPHIN_VERSION_MINOR;
}
}