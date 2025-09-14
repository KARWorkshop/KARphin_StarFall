#include <KARphin/WarpRelay/Account/BannerLoader.hpp>

#include <KARphin/IO/DirectoryStructure.hpp>

#include <map>
#include <string>
#include <vector>

#include <Common/HttpRequest.h>

#include <KARphin/Vender/json.hpp>

// downloads a banner info from the server
std::vector<uint8_t> KARphin::WarpRelay::Account::BannerLoader::DownloadBanner(const std::string& URL)
{
  Common::HttpRequest http;

  // The server always redirects once to the same location.
  http.FollowRedirects(1);

  const Common::HttpRequest::Response response = http.Get(URL);
  return response.value();
}
