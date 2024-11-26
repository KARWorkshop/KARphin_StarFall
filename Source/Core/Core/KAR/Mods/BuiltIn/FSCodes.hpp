#pragma once

// defines a built-in mod for handling fullscreen codes

#include <Common/IniFile.h>
#include <Core/GeckoCode.h>
#include <Core/GeckoCodeConfig.h>

#include <Core/KAR/Mods/Specs/GeckkoMod.hpp>

namespace KAR::Mod::BuiltIn::NA::FS
{
// enum for the option of FS
enum class FullScreenCodeIndex : uint8_t
{
  Auto = 0,  // it should be automatically set

  None,  // none code is selected

  // single port index
  Port1,
  Port2,
  Port3,
  Port4,

  // multi-screen code
  Port1_Port2,
  Port3_Port4,
  Port1_2_3,
  Port2_3_4
};

// loads the correct gecko code
inline Gecko::GeckoCode GetFSCode(const FullScreenCodeIndex& index)
{
  Common::IniFile f;
  Gecko::GeckoCode code;

  switch (index)
  {
  case FullScreenCodeIndex::Port1:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port1.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port2:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port2.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port3:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port3.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port4:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port4.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port1_Port2:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port1_2.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port3_Port4:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port3_4.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port1_2_3:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port1_2_3.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;

  case FullScreenCodeIndex::Port2_3_4:
    f.Load(Mod::ASM::GetPermaBuiltInGeckoCodePath() + "FS/Port2_3_4.ini", false);
    code = Gecko::LoadCodes(f, Common::IniFile())[0];
    code.enabled = true;
    break;
  }

  return code;
}

// removes any fs codes from a gecko stack
}  // namespace KAR::Mod::BuiltIn::NA::FS