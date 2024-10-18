#pragma once

//defines settings for the stadiums

#include "Common/Config/ConfigInfo.h"
#include "Common/Config/Enums.h"
#include "Common/Config/Config.h"

namespace KAR::Game::Stadium
{
// main settings for if stadiums are enabled
Config::Info<bool> STADIUM_IS_ENABLED_DRAG_RACE_1{{Config::System::Main, "KAR_Match_Stadium", "DragRace1"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DRAG_RACE_2{{Config::System::Main, "KAR_Match_Stadium", "DragRace2"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DRAG_RACE_3{{Config::System::Main, "KAR_Match_Stadium", "DragRace3"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DRAG_RACE_4{{Config::System::Main, "KAR_Match_Stadium", "DragRace4"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_AIR_GLIDER{{Config::System::Main, "KAR_Match_Stadium", "AirGlider"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_TARGET_FLIGHT{{Config::System::Main, "KAR_Match_Stadium", "TargetFlight"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_HIGH_JUMP{{Config::System::Main, "KAR_Match_Stadium", "HighJump"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_KIRBY_MELEE1{{Config::System::Main, "KAR_Match_Stadium", "KirbyMelee1"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_KIRBY_MELEE2{{Config::System::Main, "KAR_Match_Stadium", "KirbyMelee2"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DESTRUCTION_DERBY1{{Config::System::Main, "KAR_Match_Stadium", "DestructionDerby1"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DESTRUCTION_DERBY2{{Config::System::Main, "KAR_Match_Stadium", "DestructionDerby2"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DESTRUCTION_DERBY3{{Config::System::Main, "KAR_Match_Stadium", "DestructionDerby3"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DESTRUCTION_DERBY4{{Config::System::Main, "KAR_Match_Stadium", "DestructionDerby4"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_DESTRUCTION_DERBY5{{Config::System::Main, "KAR_Match_Stadium", "DestructionDerby5"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE1{{Config::System::Main, "KAR_Match_Stadium", "SingleRace1"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE2{{Config::System::Main, "KAR_Match_Stadium", "SingleRace2"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE3{{Config::System::Main, "KAR_Match_Stadium", "SingleRace3"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE4{{Config::System::Main, "KAR_Match_Stadium", "SingleRace4"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE5{{Config::System::Main, "KAR_Match_Stadium", "SingleRace5"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE6{{Config::System::Main, "KAR_Match_Stadium", "SingleRace6"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE7{{Config::System::Main, "KAR_Match_Stadium", "SingleRace7"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE8{{Config::System::Main, "KAR_Match_Stadium", "SingleRace8"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_SINGLE_RACE9{{Config::System::Main, "KAR_Match_Stadium", "SingleRace9"}, true};
Config::Info<bool> STADIUM_IS_ENABLED_VS_KING_DEDEDE{{Config::System::Main, "KAR_Match_Stadium", "VSKingDedede"}, true};

//extra modifer settings
Config::Info<bool> STADIUM_MODIFIER_HAS_HIGH_ITEM_FREQ{{Config::System::Main, "KAR_Match_Stadium", "VSKingDedede"}, true};

}