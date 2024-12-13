#include "textdraw_skin_select"
#include "textdraw_character_select"

stock TextDraw_OnGameModeInit() {
    SkinSelect_TD(); // Перехват в textdraw//textdraw_skin_select
    CharacterSelect_TD();
}