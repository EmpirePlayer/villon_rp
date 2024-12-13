enum {
    Text: CHARACTER_SELECT_BG,
    Text: CHARACTER_SELECT_TEXT,
    Text: CHARACTER_SELECT_TEXT_HOURS,
    Text: CHARACTER_SELECT_BG_ENTER_GAME,
    Text: CHARACTER_SELECT_TEXT_ENTER,
    MAX_CHARACTER_SELECT_GTEXTDRAWS
}
new Text: gCharacterSelectGTextDraw[MAX_CHARACTER_SELECT_GTEXTDRAWS];

stock CharacterSelect_TD() {
    gCharacterSelectGTextDraw[CHARACTER_SELECT_BG] = 
    TextDrawCreate            (147.0, 183.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gCharacterSelectGTextDraw[CHARACTER_SELECT_BG], 69.0, 17.0);
    TextDrawColor             (gCharacterSelectGTextDraw[CHARACTER_SELECT_BG], 255);
    TextDrawFont              (gCharacterSelectGTextDraw[CHARACTER_SELECT_BG], 4);

    gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT] = 
    TextDrawCreate            (149.0, 185.0, !"АККАУНТ"); // пусто
    TextDrawLetterSize        (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT], 0.1, 0.7);
    TextDrawColor             (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT], -1061109505);
    TextDrawFont              (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT], 1);
    TextDrawSetShadow         (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT], 0);

    gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_HOURS] = 
    TextDrawCreate            (149.0, 192.0, !"В_ИГРЕ"); // пусто
    TextDrawLetterSize        (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_HOURS], 0.1, 0.7);
    TextDrawColor             (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_HOURS], -1061109505);
    TextDrawFont              (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_HOURS], 1);
    TextDrawSetShadow         (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_HOURS], 0);

    gCharacterSelectGTextDraw[CHARACTER_SELECT_BG_ENTER_GAME] = 
    TextDrawCreate            (147.0, 370.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gCharacterSelectGTextDraw[CHARACTER_SELECT_BG_ENTER_GAME], 267.0, 18.0);
    TextDrawColor             (gCharacterSelectGTextDraw[CHARACTER_SELECT_BG_ENTER_GAME], 255);
    TextDrawFont              (gCharacterSelectGTextDraw[CHARACTER_SELECT_BG_ENTER_GAME], 4);

    gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER] = 
    TextDrawCreate            (280.0, 372.0, !"начать_игру"); // пусто
    TextDrawLetterSize        (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], 0.4, 1.5);
    TextDrawTextSize          (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], 9.0, 260.0);
    TextDrawColor             (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], -1061109505);
    TextDrawFont              (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], 3);
    TextDrawSetShadow         (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], 0);
    TextDrawAlignment         (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], 2);
    TextDrawSetSelectable     (gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER], true);
}