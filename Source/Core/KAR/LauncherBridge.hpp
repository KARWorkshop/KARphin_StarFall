#pragma once

//defines a bridge for sending and reciving data from the Launcher in real time

#include <string>

namespace KAR::Launcher
{
	//defines a file storing inital bridge settings
	struct LauncherBridgeConfig
	{
    std::string launcherPort = "4232";
	};

	//loads a Launcher Bridge settings file

	//writes a Launcher Bridge settings file

	//attempts to connect the launcher
	inline bool AttemptToFormBridgeToLauncher(const LauncherBridgeConfig& config)
	{
    return false;

    return true;
	}
}