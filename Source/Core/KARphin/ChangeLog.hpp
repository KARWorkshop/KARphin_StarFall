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
  "<h3> 4.3.1 - Lobby Icons!</h3>"                                                                 \
  "<p>Lobby Icons have been brought back and renamed to Banners. K3 had icons the players could choose and it would show in the lobby.<br>" \
  "They are back and redone by Taco, they are now vectorized images, meaning we can scale them as much as want.<br>" \
  "You will experiance a slight lag the first time you open the Account menu or Lobby. This should only happen once as it caches the logos. From then on it should be faster.<br>" \
  "More icons will be added as time goes on and that's partly what donations at the Kofi will be going towards. <br>" \
  "No way am I gonna let Taco (and maybe some other artists) make this sick art for free. I am paying theses skilled craftsmen the money they RIGHTFULLY DESERVE!</p>" \
  "<h4> Uploading Our Own Banners?</h4>"                                                                 \
  "<p>During K3, some users had custom icons. I do plan to bring theses back but the exact method is being worked on. <br>" \
  "The main things right now is <br>1. speeding up how banners are loading and downloaded.<br>2. It's gonna be a reward for those who support the project. <br>" \
  "If people are gonna give me money, I want to make it worth it for them. DO NOT DONATE EXPECTING CUSTOM BANNERS, AS OF RIGHT NOW IT'S NOT IMPLEMENTED!<br>" \
  "The exact details are being ironed out, but even there are custom ones. New banners are gonna be coming out for everyone to use. So you don't have to pay to use basic features. <br>" \
  "We're here to play a game, and that's always gonna be free.</p>" \
  "<h3> 4.3.1 - Minor Tweaks</h3>"                                                                \
  "<p>Added direct link to Kofi, Discord, and KAR Workshop on icon bar.</p>" \
  "<p>Froze the git hash versioning for testing if Linux can properly connect to Windows machine.</p>" \
  "<p>Revised the Warp Relay Net Settings spec.</p>" \
  "<p>KARphin cleans up some errors in the folders in the KARphin install.</p>" \
  "<p>Player Join packets wraps the Banner Info and Warp Relay spec.</p>" \


#define KARPHIN_CHANGE_LOG KARPHIN_CHANGE_LOG_4_3_1
