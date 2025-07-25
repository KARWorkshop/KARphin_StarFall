#pragma once

//defines functions for auto updating the KARphin client

#include <KARphin/IO/DirectoryStructure.hpp>

namespace KAR::Updater
{
	//defines results when we attempt to check for updates or get a update
	enum class UpdaterResult
	{
		ThereIsAUpdate = 0,

		ThereIsNoUpdate,

		CouldNotFindTheUpdater,

		Count
	};

	//checks if we have a update
	inline UpdaterResult KARphin_CheckForUpdate()
	{
    std::filesystem::path updater = KAR::IO::GetDirectory_Tools() + "Updater_KARphin.exe";
    if (!std::filesystem::exists(updater))
      return UpdaterResult::CouldNotFindTheUpdater;

		//checks for update

		return UpdaterResult::ThereIsAUpdate;
	}

	//performs a update of just the client

	//performs a full reinstall
}