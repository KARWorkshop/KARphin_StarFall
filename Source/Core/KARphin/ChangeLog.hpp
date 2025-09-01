#pragma once

//defines the change log for KAR updates

/*
-----GENERAL TO DOS--------
- patching Ignition and Deluxe in KARphin
- Tourny mode for lobbies | disables custom textures, disables the "Disable Fog" option in dolphin
- add score tracking pop up menu for matches
- slash commands in the lobby
- lobby icons
- warp relay account integration in server

---IGNITION AND LUNA SPECIFIC-------
- Use a version file in the extracted filesystem to auto-update
- sync music
- sync machine packs
- sync config files for settings
- sync city trial maps
- sync event packs
- sync item packs
- write players to ini file that can render in-game
- let port B be used for writing data back to KARphin
- Port B Luna memory card || done
*/


// 4.2.0
#define KARPHIN_CHANGE_LOG_4_2_0 \
  "<h3> 4.2.0 - Minor Changes <h3>"\
  "<p>Lowered default audio even more.</p>" \
  "<p>KARphin will now appear as the discord activity by default</p>" \
  "<p>Right click a game and click wiki now opens our wiki</p>" \
  "<p>If the ROM disables memory cards, it will now disable the KWQI option for downloading memory cards.</p>" \
  "<p>Fixed bug with auto updater not checking major, minor, and hotfix priority.</p>" \
  "<p>About section now renders current change log and description changes.</p>"

#define KARPHIN_CHANGE_LOG KARPHIN_CHANGE_LOG_4_2_0