#pragma once

//defines KAR Workshop Quick Install operations for downloading memory cards

#include <Common/HttpRequest.h>

#include <KARphin/IO/DirectoryStructure.hpp>

namespace KWQI::MemoryCard
{
	//downloads the memory card at the chosen URL
static inline bool DownloadMemoryCard(const std::string& memoryCardURL,
                                      const std::string& region = "USA",
                                      const std::string& filenameForOutputedMemoryCard = "NetplayMemCard")
	{
    Common::HttpRequest http;

    // The server always redirects once to the same location.
    http.FollowRedirects(1);

    const Common::HttpRequest::Response response = http.Get(memoryCardURL);
    std::string FP = "";
    if (response.has_value())  // writes the image to cache
    {
      // packs data
      const std::vector<uint8_t> data = response.value();
      FP = KAR::IO::GetDirectory_MemoryCards() + filenameForOutputedMemoryCard + "." + region + ".raw";
      File::CreateEmptyFile(FP);
      std::ofstream outFile(FP, std::ios::binary);
      outFile.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
      outFile.close();

      return true;
    }

    //we failed
  return false;
  }
  }