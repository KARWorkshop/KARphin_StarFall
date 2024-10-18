#pragma once

//defines a few network backend stuff

namespace KAR::Networking::Util
{
	//defines a connection type
	enum class NetworkConnectionType
	{
		Direct_IP = 0, //uses a IP and port to connect to someone

		//Direct_LAN, //connects to users on a LAN network

		Online_HostCode, //uses a host code generated by someone to connect online, isn't on the same network

		//Online_FriendCode, //uses a perment generated code for a Account
		//Online_MatchMaking, //connects to a user randomly using online match making

		Count
	};

	//which backend are we using
	enum class NetworkBackend
	{
		Dolphin = 0, //default, first implementation, uses standard Dolphin STUN server and room data request

		WarpRelay, //our custom one and one used with accounts and such

		Count
	};

	//returns Dolphin's STUN server address
  static std::string GetSTUNServer_Address_Dolphin()
  {
    return "stun.dolphin-emu.org";
  }

	//returns Dolphin's STUN server port
  static u16 GetSTUNServer_Port_Dolphin()
  {
    return 0x1876;
  }

  }