#pragma once

//defines functions to let us auto update KARphin

#include <KARphin/Version.hpp>

#include <Common/HttpRequest.h>

#include <KARphin/IO/DirectoryStructure.hpp>

namespace KAR::AutoUpdate::KARphin
{
// checks if KARphin needs a update
static inline bool CheckForKARphinUpdate()
{
  // gets the URL from the KWQI data
  const std::string MEMORY_CARD_URL =
      "https://github.com/KARWorkshop/KARphin_StarFall/releases/download/Dist/manifest.karphin";

  // gets the image
  // std::string endpoint{URL};
  Common::HttpRequest http;

  // The server always redirects once to the same location.
  http.FollowRedirects(1);

  const Common::HttpRequest::Response response = http.Get(MEMORY_CARD_URL);
  std::string FP = "";
  if (response.has_value())  // writes the image to cache
  {
    // packs data
    const std::vector<uint8_t> data = response.value();
    FP = File::GetExeDirectory() + DIR_SEP + "manifetsOnline";
    File::CreateEmptyFile(FP);
    std::ofstream outFile(FP, std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
    outFile.close();

    // checks if the update is needed
    KAR::Version::ManifestVersionData online = KAR::Version::LoadManifestFile(FP);
    if (online.isDist != KARPHIN_BUILD_IS_DIST || online.major > KARPHIN_VERSION_MAJOR ||
        online.minor > KARPHIN_VERSION_MINOR || online.hotfix > KARPHIN_VERSION_HOTFIX)
      return true;
  }

  return false;
}

// downloads the latest zip
static inline void DownloadLatestBuild()
{
  // gets the URL from the KWQI data
  const std::string MEMORY_CARD_URL = "https://github.com/KARWorkshop/KARphin_StarFall/releases/"
                                      "download/Dist/KARphin_Win.ignitionKey";

  // gets the image
  // std::string endpoint{URL};
  Common::HttpRequest http;

  // The server always redirects once to the same location.
  http.FollowRedirects(1);

  const Common::HttpRequest::Response response = http.Get(MEMORY_CARD_URL);
  std::string FP = "";
  if (response.has_value())  // writes the image to cache
  {
    // packs data
    const std::vector<uint8_t> data = response.value();
    FP = File::GetExeDirectory() + DIR_SEP + "KARphin.ignitionKey";
    File::CreateEmptyFile(FP);
    std::ofstream outFile(FP, std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
    outFile.close();
  }
}
}  // namespace KAR::AutoUpdate::KARphin