#pragma once

//defines various Star Settings for a match

#include "Common/Config/ConfigInfo.h"
#include "Common/Config/Enums.h"
#include "Common/Config/Config.h"

namespace KAR::Game::Star
{
// main settings for stars in the match
Config::Info<bool> STAR_IS_ENABLED_SWERVE_STAR{{Config::System::Main, "KAR_Match_Stars_Spawn", "SwerveStar"}, true};

//extra backside codes || only work in a Backside ROM or Backside based ROM
Config::Info<bool> STAR_IS_ENABLED_BACKSIDE_LANCE_AND_SOAR_STARS{{Config::System::Main, "KAR_Match_Stars_Spawn", "Backside_SoarAndLance"}, true};
} 