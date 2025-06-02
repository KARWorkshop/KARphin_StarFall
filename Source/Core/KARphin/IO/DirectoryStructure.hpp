#pragma once

//defines various structures for getting/creating needed directories

#include <Common/FileUtil.h>
#include <Common/CommonPaths.h>

namespace KAR::IO
{
  //gets/creates directories if they are missing
  static inline std::string CreateDirIfMissing(const std::string& dir)
  {
    if (File::CreateFullPath(dir))
      File::CreateDirs(dir);
    return dir;
  }

	//gets/creates the directory for all Memory Cards
	static inline std::string GetDirectory_MemoryCards()
	{
    return CreateDirIfMissing(File::GetExeDirectory() + DIR_SEP + ".." + DIR_SEP + "MemoryCards" + DIR_SEP);
	}

  // gets/creates the directory for all ROMs
  static inline std::string GetDirectory_ROMs()
  {
    return CreateDirIfMissing(File::GetExeDirectory() + DIR_SEP + ".." + DIR_SEP + "ROMs" +
                              DIR_SEP);
  }

  // gets/creates the directory for all Mods
  static inline std::string GetDirectory_Mods()
  {
    return CreateDirIfMissing(File::GetExeDirectory() + DIR_SEP + ".." + DIR_SEP + "Mods" +
                              DIR_SEP);
  }

  // gets/creates the sub-directory in Mods for Gecko Codes
  static inline std::string GetDirectory_GeckoCodes()
  {
    return CreateDirIfMissing(GetDirectory_Mods() + "GeckoCodes" + DIR_SEP);
  }

  // gets/creates the sub-directory in Mods for Loading textures and such
  static inline std::string GetDirectory_CustomLoadAssets()
  {
    return CreateDirIfMissing(GetDirectory_Mods() + "Load" + DIR_SEP);
  }

	// gets/creates the directory for all core client settings
  static inline std::string GetDirectory_CoreClientSettings()
  {
    return CreateDirIfMissing(File::GetExeDirectory() + DIR_SEP + PORTABLE_USER_DIR + DIR_SEP);
  }

  }