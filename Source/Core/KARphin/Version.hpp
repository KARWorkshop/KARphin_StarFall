#pragma once

//defines versioning info for KARphin

#include <Common/FileUtil.h>
#include <KARphin/Vender/json.hpp>

#include <KARphin/ChangeLog.hpp>

#include <string>

#define KARPHIN_VERSION_MAJOR 4
#define KARPHIN_VERSION_MINOR 4
#define KARPHIN_VERSION_HOTFIX 0
#define KARPHIN_BUILD_IS_DIST true

#define KARPHIN_BUILD_TYPE_DISTRIBUTION "Dist"
#define KARPHIN_BUILD_TYPE_DEV "Dev"

namespace KAR::Version
{
  //returns a version string
static inline std::string GetVersionString_Full()
{
  return std::to_string(KARPHIN_VERSION_MAJOR) + "." + std::to_string(KARPHIN_VERSION_MINOR) + "." +
         std::to_string(KARPHIN_VERSION_HOTFIX) + " - " +
         (KARPHIN_BUILD_IS_DIST == true ? KARPHIN_BUILD_TYPE_DISTRIBUTION :
                                          KARPHIN_BUILD_TYPE_DEV);
}

// stores the KARphin manifest version data
struct ManifestVersionData
{
  uint32_t major = 0, minor = 0, hotfix = 0;
  bool isDist = true;
  std::string changeLog = "NO CHANGE LOG DATA LOADED";

  // returns a version string
  inline std::string GetVersionString_Full()
  {
    return std::to_string(major) + "." + std::to_string(minor) +
           "." + std::to_string(hotfix) + " - " +
           (isDist == true ? KARPHIN_BUILD_TYPE_DISTRIBUTION :
                                            KARPHIN_BUILD_TYPE_DEV);
  }
};


//writes a manifest file for versioning
static inline void WriteManifestFile()
{
  nlohmann::json manifest;
  manifest["major"] = KARPHIN_VERSION_MAJOR;
  manifest["minor"] = KARPHIN_VERSION_MINOR;
  manifest["hotfix"] = KARPHIN_VERSION_HOTFIX;
  manifest["build"] = KARPHIN_BUILD_IS_DIST;
  manifest["changeLog"] = KARPHIN_CHANGE_LOG;

  File::CreateEmptyFile(File::GetExeDirectory() + "/" + "manifest.karphin");
  File::WriteStringToFile(File::GetExeDirectory() + "/" + "manifest.karphin", manifest.dump());
}

 // loads the manifest version file
static inline ManifestVersionData LoadManifestFile(const std::filesystem::path manifestFilepath)
{
  ManifestVersionData data;

  std::string jsonData = "";
  if (!File::ReadFileToString(manifestFilepath.string(), jsonData))
    return data;

  nlohmann::json manifestVer = nlohmann::json::parse(jsonData);

  data.major = manifestVer["major"].get<uint32_t>();
  data.minor = manifestVer["minor"].get<uint32_t>();
  data.hotfix = manifestVer["hotfix"].get<uint32_t>();
  data.isDist = manifestVer["build"].get<bool>();

  if (manifestVer.contains("changeLog"))
    data.changeLog = manifestVer["changeLog"].get<std::string>();

  return data;
}

}