enum {
    /*
      Глобальные TextDraw выбора скина
    */
    Text: SELECT_SKIN_BG,
    Text: SELECT_SKIN_TEXT,

    Text: SELECT_SKIN_BG_EUROPEAN,
    Text: SELECT_SKIN_TEXT_EUROPEAN,

    Text: SELECT_SKIN_BG_AFROAMERICAN,
    Text: SELECT_SKIN_TEXT_AFROAMERICAN,

    Text: SELECT_SKIN_BG_LATINOS,
    Text: SELECT_SKIN_TEXT_LATINOS,

    Text: SELECT_SKIN_BG_ASIAN,
    Text: SELECT_SKIN_TEXT_ASIAN,

    Text: SELECT_SKIN_BG_1,

    Text: SELECT_SKIN_BG_NEXT,
    Text: SELECT_SKIN_TEXT_NEXT,

    Text: SELECT_SKIN_BG_PREV,
    Text: SELECT_SKIN_TEXT_PREV,

    Text: SELECT_SKIN_BG_SETTING,
    Text: SELECT_SKIN_TEXT_SETTING,

    Text: SELECT_SKIN_BG_MALE,
    Text: SELECT_SKIN_TEXT_MALE,

    Text: SELECT_SKIN_BG_FEMALE,
    Text: SELECT_SKIN_TEXT_FEMALE,

    Text: SELECT_SKIN_BG_AGE,
    Text: SELECT_SKIN_L_ARROWS_AGE,
    Text: SELECT_SKIN_R_ARROWS_AGE,

    Text: SELECT_SKIN_BG_ANIMS,
    Text: SELECT_SKIN_L_ARROWS_ANIMS,
    Text: SELECT_SKIN_R_ARROWS_ANIMS,

    Text: SELECT_SKIN_BG_FINISH,
    Text: SELECT_SKIN_TEXT_FINISH,

    MAX_SELECT_SKIN_GTEXTDAWS
}
new Text: gSelectSkinGTextDraw[MAX_SELECT_SKIN_GTEXTDAWS];

stock SkinSelect_TD(){
    gSelectSkinGTextDraw[SELECT_SKIN_BG] = 
    TextDrawCreate            (74.0, 134.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG], 123.16, 13.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG], COLOR_WHITE);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG], 4);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT] = 
    TextDrawCreate            (110.0, 135.0, !"ВЫБОР_ОДЕЖДЫ"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT], 0.2, 1.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT], 858993663);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_EUROPEAN] = 
    TextDrawCreate            (74.0, 150.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_EUROPEAN], 55.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_EUROPEAN], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_EUROPEAN], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_EUROPEAN], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_EUROPEAN] = 
    TextDrawCreate            (83.0, 153.0, !"ЕВРОПЕОИДНАЯ"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_EUROPEAN], 0.14, 0.8);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_EUROPEAN], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_EUROPEAN], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_EUROPEAN], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_AFROAMERICAN] = 
    TextDrawCreate            (74.0, 166.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_AFROAMERICAN], 55.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_AFROAMERICAN], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_AFROAMERICAN], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_AFROAMERICAN], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_AFROAMERICAN] = 
    TextDrawCreate            (79.0, 169.0, !"АФРО_АМЕРИКАНЕЦ"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_AFROAMERICAN], 0.14, 0.8);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_AFROAMERICAN], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_AFROAMERICAN], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_AFROAMERICAN], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_LATINOS] = 
    TextDrawCreate            (74.0, 182.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_LATINOS], 55.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_LATINOS], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_LATINOS], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_LATINOS], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_LATINOS] = 
    TextDrawCreate            (89.0, 185.0, !"ЛАТИНОС"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_LATINOS], 0.14, 0.8);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_LATINOS], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_LATINOS], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_LATINOS], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_ASIAN] = 
    TextDrawCreate            (74.0, 198.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_ASIAN], 55.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_ASIAN], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_ASIAN], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_ASIAN], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_ASIAN] = 
    TextDrawCreate            (93.0, 201.0, !"АЗИАТ"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_ASIAN], 0.14, 0.8);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_ASIAN], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_ASIAN], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_ASIAN], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_1] = 
    TextDrawCreate            (130.0, 150.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_1], 3.0, 63.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_1], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_1], 4);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT] = 
    TextDrawCreate            (166.0, 215.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT], 31.0, 9.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT] = 
    TextDrawCreate            (175.0, 216.0, !"ВПЕРЕД"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT], 0.1, 0.7);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV] = 
    TextDrawCreate            (134.0, 215.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV], 31.0, 9.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV] = 
    TextDrawCreate            (143.0, 216.0, !"НАЗАД"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV], 0.1, 0.7);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_SETTING] = 
    TextDrawCreate            (74.0, 226.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_SETTING], 123.16, 13.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_SETTING], COLOR_WHITE);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_SETTING], 4);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_SETTING] = 
    TextDrawCreate            (95.6, 228.0, !"НАСТРОЙКИ_ПЕРСОНАЖА"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_SETTING], 0.2, 1.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_SETTING], 858993663);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_SETTING], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_SETTING], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_MALE] = 
    TextDrawCreate            (74.0, 241.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_MALE], 60.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_MALE], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_MALE], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_MALE], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_MALE] = 
    TextDrawCreate            (87.0, 244.0, !"МУЖЧИНА"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_MALE], 0.2, 1.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_MALE], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_MALE], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_MALE], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_FEMALE] = 
    TextDrawCreate            (138.0, 241.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_FEMALE], 60.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_FEMALE], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_FEMALE], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_FEMALE], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FEMALE] = 
    TextDrawCreate            (153.0, 244.0, !"ЖЕНЩИНА"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FEMALE], 0.2, 1.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FEMALE], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FEMALE], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FEMALE], 0);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_AGE] = 
    TextDrawCreate            (74.0, 257.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_AGE], 124.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_AGE], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_AGE], 4);

    gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE] = 
    TextDrawCreate            (85.0, 260.0, !"<<<"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE], 0.2, 1.0);
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE], 9.0000, 15.0000);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE], 0);
    TextDrawAlignment         (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE], 2);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE], true);

    gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE] = 
    TextDrawCreate            (188.0, 260.0, !">>>"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE], 0.2, 1.0);
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE], 9.0, 15.0);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE], 0);
    TextDrawAlignment         (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE], 2);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE], true);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_ANIMS] = 
    TextDrawCreate            (74.0, 274.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_ANIMS], 124.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_ANIMS], 118098431);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_ANIMS], 4);

    gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS] = 
    TextDrawCreate            (85.0, 277.0, !"<<<"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS], 0.2, 1.0);
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS], 9.0, 15.0);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS], 0);
    TextDrawAlignment         (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS], 2);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS], true);

    gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS] = 
    TextDrawCreate            (188.0, 277.0, !">>>"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS], 0.2, 1.0);
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS], 9.0, 15.0);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS], 0);
    TextDrawAlignment         (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS], 2);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS], true);

    gSelectSkinGTextDraw[SELECT_SKIN_BG_FINISH] = 
    TextDrawCreate            (74.0, 291.0, !"LD_SPAC:white"); // пусто
    TextDrawTextSize          (gSelectSkinGTextDraw[SELECT_SKIN_BG_FINISH], 124.0, 15.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_BG_FINISH], COLOR_BLUE);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_BG_FINISH], 4);
    TextDrawSetSelectable     (gSelectSkinGTextDraw[SELECT_SKIN_BG_FINISH], true);

    gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FINISH] = 
    TextDrawCreate            (121.0, 294.0, !"ЗАВЕРШИТЬ"); // пусто
    TextDrawLetterSize        (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FINISH], 0.2, 1.0);
    TextDrawColor             (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FINISH], -1);
    TextDrawFont              (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FINISH], 1);
    TextDrawSetShadow         (gSelectSkinGTextDraw[SELECT_SKIN_TEXT_FINISH], 0);

    #if DEBUG_MODE
      print(!">> PLAYER_SKIN_SELECT TEXTDRAW CREATE");
    #endif
}