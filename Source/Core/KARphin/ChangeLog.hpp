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
/*#define KARPHIN_CHANGE_LOG_4_2_0 \
  "<h3> 4.2.1 - Fixed the update to fix the update<h3>"                                                                \
  "<p> adjusted change log versioning check, hopefully for the last time, if more issues persist with always showing the update let Jas know.</p>" \
  "<h3> 4.2.0 - Can force the port <h3>"                                                                \
  "<p>Using the dropdown in the Lobby, you can force the port to see, but 90% of the time you can left it at Auto.</p>"                                                        \
  "<h3> 4.2.0 - Minor Changes <h3>"\
  "<p>Lowered default audio even more.</p>" \
  "<p>KARphin will now appear as the discord activity by default</p>" \
  "<p>Right click a game and click wiki now opens our wiki</p>" \
  "<p>If the ROM disables memory cards, it will now disable the KWQI option for downloading memory cards.</p>" \
  "<p>Fixed bug with auto updater not checking major, minor, and hotfix priority.</p>" \
  "<p>About section now renders current change log and description changes.</p>"
*/

//4.3.XXXXX
/*#define KARPHIN_CHANGE_LOG_4_3_0 \
  "<h3> 4.3.0 - KWQI file integration</h3>" \
  "<p>KAR Workshop Quick Install (KWQI) are now fully integrated. Deluxe and Backside are baked into KARphin." \
  "<br>The spec and tooling are still being ironed out, so KARphin's internals might change for how KWQI works.<br>" \
  "Modders will be worked with to make a API and spec that supports their goals and what is feasiable.</p>" \
  "<h3> 4.3.0 - Spectating</h3>" \
  "<p>There is now a spectate button for joining as a spectator. This just unports you, saving a step for streamers.</p>" \
  "<h3> 4.3.0 - Minor Stuff</h3>"                                                                   \
  "<p>On Connection packets now are compressed and uncompressed into a custom Warp Relay spec-ed struct.</p>" \
  "<p>Tweaked the host warning message to be KARphin related</p>" \
  "<p>Cleaned up some left over code brought from K3 for icons.</p>" \
*/

#define KARPHIN_CHANGE_LOG_4_3_1                                                                   \
  "<h3> 4.3.1 - Minor Tweaks</h3>"                                                                \
  "<p>Added direct link to Kofi and Discord on icon bar.</p>" \
  "<p>Mods menu added, but lacking full implementation</p>" \


#define KARPHIN_CHANGE_LOG KARPHIN_CHANGE_LOG_4_3_1
