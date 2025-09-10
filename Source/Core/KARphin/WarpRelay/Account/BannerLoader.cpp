#include <KARphin/WarpRelay/Account/BannerLoader.hpp>

#include <map>
#include <string>
#include <vector>

#include <Common/HttpRequest.h>

static std::map<std::string, std::vector<uint8_t>>
    binaryIcons;  // stores the icons in RAM so we can just pack them into the tables as needed

//downloads the icon
static inline std::vector<uint8_t> DownloadIcon(const std::string& URL)
{
  std::vector<uint8_t> data;

  Common::HttpRequest http;

  // The server always redirects once to the same location.
  http.FollowRedirects(1);

  const Common::HttpRequest::Response response = http.Get(URL);
  std::string FP = "";
  if (response.has_value())  // writes the image to cache
  {
    // packs data
    data = response.value();
  }

  return data;
}

// gets the Icon data based on a URL, if it doesn't exist, load it
std::vector<uint8_t>& KARphin::WarpRelay::Account::GetIcon(const std::string& URL)
{
  // checks for their icon, if it doesn't exist we download it
  if (binaryIcons.find(URL) == binaryIcons.end())
    binaryIcons[URL] = DownloadIcon(URL);

  return binaryIcons.at(URL);
}
