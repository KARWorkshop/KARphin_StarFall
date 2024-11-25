#pragma once

//handles generating pre-built memory cards for supported games

#include <Core/KAR/Mods/MemoryCards/HPMemoryCard.hpp>
#include <Core/KAR/GameIDs.hpp>

#include "Common/FileUtil.h" //<Core/Common/FileUtil.h>

namespace KAR::Mod::BuiltIn::Memory
{
	//stores the differant memory cards we generate
	enum class MemoryCard
	{
		None = 0x00, //where no memory card should be set

		HackPack, //sets a preconfigured memory card for Hack Pack

		BacksideV2,  // sets a preconfigured memory card for Hack Pack
	};

	//gets the memory card type based on the game ID
	static inline MemoryCard GetMemoryCardTypeFromGameID(const std::string& gameID)
	{
		if (gameID == GameData::GetGameID_HP())
		{
      return MemoryCard::HackPack;
		}

		return MemoryCard::None;
	}

	//gets a memory card based on the type given
	static inline unsigned char* GetMemoryCard_DataArray(const MemoryCard& card)
	{
		switch (card)
		{
    case MemoryCard::HackPack:
      return HP_RAW_MEMORY_CARD_DEFAULT;
		}

    return nullptr;
	}

	//gets the name of the memory card
  static inline std::string GetMemoryCard_Name(const MemoryCard& card)
  {
    switch (card)
    {
    case MemoryCard::HackPack:
      return "HackPack";
    }

    return "";
  }

	// gets the long name of the memory card
  static inline std::string GetMemoryCard_LongDisplayName(const MemoryCard& card)
  {
    switch (card)
    {
    case MemoryCard::HackPack:
      return "Hack Pack 1.0.1";
    }

    return "";
  }

	//gets the path to where the memory card will be written
	static inline std::string GetMemoryCard_Path(const MemoryCard& card)
	{
		switch (card)
		{
    case MemoryCard::HackPack:
      return File::GetExeDirectory() + "/MemoryCards/" + GetMemoryCard_Name(card) + ".USA.raw";
		}

		return "";
	}

	//generates the chosen memory card
	static inline void GenerateMemoryCard(const MemoryCard& card)
	{
    const std::string memoryCardPath = GetMemoryCard_Path(card);
    if (memoryCardPath == "") //don't gen one if it's not a supported one
      return;

    // Open file in binary write mode
    File::CreateEmptyFile(memoryCardPath);
    FILE* file = fopen(memoryCardPath.c_str(), "wb");
    if (file == NULL)
    {
      // perror("Error opening file");
      //  return EXIT_FAILURE;
      return;
    }

    // Write the binary array to the file
    unsigned char* memCard = GetMemoryCard_DataArray(card);
    const size_t memCardByteSize = sizeof(memCard);
    size_t written = fwrite(memCard, sizeof(unsigned char), memCardByteSize, file);
    if (written != memCardByteSize)
    {
      // perror("Error writing to file");
      fclose(file);
      // return EXIT_FAILURE;
    }

    // Close the file
    fclose(file);
	}
  }