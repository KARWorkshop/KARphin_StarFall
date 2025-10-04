#pragma once

/*
Net Config Data - this is a small file/struct that stores the info this runner uses for connecting with the BBA
									this data is normally written by the KAR Online frontend/launcher
*/

#include <steam/steamnetworkingsockets.h>
#include <steam/isteamnetworkingutils.h>

#include <Common/FileUtil.h>

#include <KARphin/Vender/json.hpp>

#include <Common/FileUtil.h>
#include <Common/CommonPaths.h>

namespace KAR::Online
{
	//defines the net info data
	struct NetInfo
	{
    bool isHost = false; //is this instance a host or client
    SteamNetworkingIPAddr IP_Port; //the IP and port
    std::string debugIPStr = ""; //stores the debug IP as string for printing

		//geenrates a default net info
		static inline NetInfo GenerateDefault()
		{
			NetInfo info;
      info.isHost = true;
      info.IP_Port.SetIPv6LocalHost(6969);
      return info;
		}

		//gets the filepath for a net info file
    static inline std::string GetFilepath()
    {
      return File::GetExeDirectory() + DIR_SEP + "netinfo.Konline";
    }

		//saves the net info to disc
		inline void SaveToDisc()
		{
      char szAddr[SteamNetworkingIPAddr::k_cchMaxString];
      IP_Port.ToString(szAddr, sizeof(szAddr), true);

			nlohmann::json data;
      data["isHost"] = isHost;
      data["IP"] = szAddr;

			if (std::filesystem::exists(GetFilepath()))
        std::filesystem::remove(GetFilepath());
      File::CreateEmptyFile(GetFilepath());
      File::WriteStringToFile(GetFilepath(), data.dump());
		}

		//loads the net info from disc
    inline void LoadFromDisc()
    {
      if (!std::filesystem::exists(GetFilepath()))
        return;

      std::string dataStr = "";
      File::ReadFileToString(GetFilepath(), dataStr);

      nlohmann::json data = nlohmann::json::parse(dataStr);
      if (data.contains("isHost"))
        isHost = data["isHost"].get<bool>();
      if (data.contains("IP"))
      {
        debugIPStr = data["IP"].get<std::string>();
        IP_Port.ParseString(debugIPStr.c_str());
      }
    }

	};
}