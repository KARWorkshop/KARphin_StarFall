#pragma once

//defines a warp relay account icon manager

#include <qicon.h>

#include <Common/HttpRequest.h>
#include <Common/FileUtil.h>

namespace KAR::WarpRelay::IconLoader
{

// the downloaded custom icons, maps a URL to a FP of image
static std::map<std::string, std::string> iconFPs;
// stores a map of Icon byte data to arrays to their URLs
static std::unordered_map<std::string, QIcon> icons;

//the perma path for the fullback image
static inline std::string FallbackImageFP()
{
  return File::GetExeDirectory() + "/Sys/NetIconFallback.png";
}

//downloads a image from the internet
static inline QPixmap DownloadIcon(const std::string URL)
{
  QPixmap pixmap;

  // gets the image
  Common::HttpRequest http;

  // The server always redirects once to the same location.
  http.FollowRedirects(1);

  const Common::HttpRequest::Response response = http.Get(URL);
  std::string FP = "";
  if (response.has_value())  // writes the image to cache
  {
    // net cache
    const std::string netCacheDir = File::GetExeDirectory() + "/NetCache/";
    if (!File::Exists(netCacheDir))
      File::CreateDir(netCacheDir);

    // packs data
    const std::vector<uint8_t> data = response.value();
    FP = netCacheDir + "Data" + std::to_string(icons.size()) + ".png";
    File::CreateEmptyFile(FP);
    std::ofstream outFile(FP, std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
    outFile.close();
  }
  else  // if we failed, fallback
    FP = FallbackImageFP();

  // loads data
  iconFPs[URL] = FP;
  pixmap.load(QString::fromStdString(FP));

  return pixmap;
}

//gets the icon, if it doesn't exist we load it
static inline QIcon GetIcon(const std::string& URL)
{
  // checks for their icon, if it doesn't exist we download it
  if (icons.find(URL) == icons.end())
    icons[URL] = QIcon(DownloadIcon(URL));

  return icons.at(URL);
}

}  // namespace KAR::WarpRelay::IconLoader