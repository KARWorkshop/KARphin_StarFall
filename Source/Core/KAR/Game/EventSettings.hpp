#pragma once

//defines a block of settings for events

#include "Common/Config/ConfigInfo.h"
#include "Common/Config/Enums.h"
#include "Common/Config/Config.h"

namespace KAR::Game::Event
{
  //main settings for if events are enabled
	Config::Info<bool> EVENT_IS_ENABLED_DYNO_BLADE{{Config::System::Main, "KAR_Match_Event", "DynoBlade"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_TAC{{Config::System::Main, "KAR_Match_Event", "Tac"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_METEOR{{Config::System::Main, "KAR_Match_Event", "Meteor"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_PILLAR{{Config::System::Main, "KAR_Match_Event", "Pillar"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_RUN_AMOK{{Config::System::Main, "KAR_Match_Event", "RunAmok"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_RESTORATION_AREA{{Config::System::Main, "KAR_Match_Event", "RestorationArea"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_RAILWAY_FIRE{{Config::System::Main, "KAR_Match_Event", "RailwayFire"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_BOXES_HAVE_SAME_ITEM{{Config::System::Main, "KAR_Match_Event", "BoxesHaveSameItem"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_LIGHT_HOUSE{{Config::System::Main, "KAR_Match_Event", "Lighthouse"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_SECRET_CHAMBER{{Config::System::Main, "KAR_Match_Event", "SecretChamber"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_PREDICTION{{Config::System::Main, "KAR_Match_Event", "Prediction"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_MACHINE_FORMATION{{Config::System::Main, "KAR_Match_Event", "MachineFormation"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_UFO{{Config::System::Main, "KAR_Match_Event", "UFO"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_ITEM_BOUNCE{{Config::System::Main, "KAR_Match_Event", "ItemBounce"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_DENSE_FOG{{Config::System::Main, "KAR_Match_Event", "DenseFog"}, true};
  Config::Info<bool> EVENT_IS_ENABLED_FAKE_POWERUPS{{Config::System::Main, "KAR_Match_Event", "FakePowerUps"}, true};

  //extra settings
  Config::Info<float> EVENT_MODIFIER_TIME_BETWEEN_EVENTS{{Config::System::Main, "KAR_Match_Event", "TimeBetweenEvents"}, 0.0f}; //in seconds
  Config::Info<float> EVENT_MODIFIER_INITAL_EVENT_DELAY_TIME{{Config::System::Main, "KAR_Match_Event", "InitalDelayTillEvents"}, 0.0f};  // in seconds
  Config::Info<bool> EVENT_MODIFIER_ALLOW_DUPLICATE_EVENTS{{Config::System::Main, "KAR_Match_Event", "AllowDuplicateEvents"}, false};

  //event modifiers
}