#pragma once

//defines versioning info for KARphin

#include <Common/FileUtil.h>
#include <KARphin/Vender/json.hpp>

#include <string>

#define KARPHIN_VERSION_MAJOR 4
#define KARPHIN_VERSION_MINOR 0
#define KARPHIN_VERSION_HOTFIX 0
#define KARPHIN_BUILD_IS_DIST false

#define KARPHIN_BUILD_TYPE_DISTRIBUTION "Dist"
#define KARPHIN_BUILD_TYPE_DEV "Dev"

namespace KAR::Version
{

//writes a manifest file for versioning
static inline void WriteManifestFile()
{
  nlohmann::json manifest;
  manifest["major"] = KARPHIN_VERSION_MAJOR;
  manifest["minor"] = KARPHIN_VERSION_MINOR;
  manifest["hotfix"] = KARPHIN_VERSION_HOTFIX;
  manifest["build"] = KARPHIN_BUILD_IS_DIST;

  File::CreateEmptyFile(File::GetExeDirectory() + "/" + "manifest.karphin");
  File::WriteStringToFile(File::GetExeDirectory() + "/" + "manifest.karphin", manifest.dump());
}

}