#define SKIN_SELECT_SPACE_SLOT_X    32
#define SKIN_SELECT_SPACE_SLOT_Y    32

#define MAX_SKIN_NATIONAL           4     
#define MAX_SKIN_ON_PAGE			4 			/* Сколько скинов будет на одной странице */        

new 
    pVar__AntiFlood_Skin[] = !"pVar__AntiFlood_Skin",
    pVar__AntiFlood_Anims[] = !"pVar__AntiFlood_Anims",
    pVar__SelectSkin[] = !"pVar__SelectSkin",
    pVar__SelectSkin_Page[] = !"pVar__SelectSkin_Page",
    pVar__SelectSkin_MaxPage[] = !"pVar__SelectSkin_MaxPage",
    pTimerClearAnims[MAX_PLAYERS] = {INVALID_PLAYER_TIMER_ID, ...},
    pObjectsPlayerSelectSkin[MAX_PLAYERS][93] /* Интьер выбора скина */
; 

new const
    gRegSkins[MAX_SKIN_NATIONAL][2][10] = {
        // Европеоедная
        {
            {10, 38, 55, 90, 91, 93, 152, 192}, // Женские
            {15, 20, 23, 29, 60, 72, 96, 101, 170, 206} // Мужские
        }, 
        //Афро Американец
        {
            {9, 13, 256}, // Женские
            {4, 7, 14, 21, 22} // Мужские
        },
        //Латинос
        {
            {12, 40, 190, 214}, // Женские
            {30, 47, 48, 184, 292, 44} // Мужские
        },
        //Азиат
        {
            {169, 224, 263}, // Женские
            {49, 58, 119, 180, 185, 229, } // Мужские
        }
};

enum {
    PlayerText: P_SKIN_SELECT_CELL_SKIN[MAX_SKIN_ON_PAGE],
    MAX_SELECT_SKIN_PTEXTDRAWS
}
new PlayerText: pTextDrawSelectSkin[MAX_PLAYERS][MAX_SELECT_SKIN_PTEXTDRAWS];

enum {
    PlayerText: P_SKIN_SELECT_TEXT_AGE,
    PlayerText: P_SKIN_SELECT_TEXT_STYLE_CHAT,
    MAX_SELECT_SKIN_PTEXTDRAWS_AGE
}

new PlayerText: pTextDrawSelectAge[MAX_PLAYERS][MAX_SELECT_SKIN_PTEXTDRAWS_AGE];

stock PlayerGotoSkinSelect(playerid) {
    CreateInteriorSelectSkin(playerid);

    PlayerClearChat(playerid);
    PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);

    TogglePlayerControllable(playerid, false);

    SetPlayerPos(playerid, -2238.0168, 1249.9298, 87.6523);
    SetPlayerCameraPos(playerid, -2234.2095, 1247.3082, 89.0105);
    SetPlayerCameraLookAt(playerid, -2238.0168, 1249.9298, 87.6523);
    SetPlayerFacingAngle(playerid, 180.0);

    SetPVarInt(playerid, pVar__SelectSkin, 1);
    SetPVarInt(playerid, pVar__SelectSkin_Page, 1);

    CreatePlayerTextDrawSkin(playerid, 1);

    for(new i = 0; i < MAX_SELECT_SKIN_GTEXTDAWS; i++) {
        if(GetPVarInt(playerid, pVar__SelectSkin_MaxPage) <= 1 && (i == SELECT_SKIN_BG_NEXT || i == SELECT_SKIN_TEXT_NEXT) || (i == SELECT_SKIN_BG_PREV || i == SELECT_SKIN_TEXT_PREV))
            continue;

        TextDrawShowForPlayer(playerid, gSelectSkinGTextDraw[i]);
    }
    SelectTextDraw(playerid, COLOR_GREY);

    ApplyAnimation(
        playerid,
        !"CLOTHES", !"CLO_POSE_LOOP",
        4.1, true, false, false, false, 0, false
    );

    player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
    SetPlayerSkin(playerid, player_info[playerid][p_Skin]);

    pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE] = 
    CreatePlayerTextDraw            (playerid, 120.0, 260.0, !"ВОЗРАСТ_18"); // пусто
    PlayerTextDrawLetterSize        (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE], 0.2, 1.0);
    PlayerTextDrawColor             (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE], -1);
    PlayerTextDrawFont              (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE], 1);
    PlayerTextDrawSetShadow         (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE], 0);
    PlayerTextDrawShow 			    (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE]);

    pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT] = 
    CreatePlayerTextDraw            (playerid, 111.0, 277.0, !"ЖЕСТИКУЛЯЦИЯ_1"); // пусто
    PlayerTextDrawLetterSize        (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT], 0.2, 1.0);
    PlayerTextDrawColor             (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT], -1);
    PlayerTextDrawFont              (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT], 1);
    PlayerTextDrawSetShadow         (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT], 0);
    PlayerTextDrawShow 			    (playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT]);
}

stock CreatePlayerTextDrawSkin(playerid, const value) {
    new Float:count_skins = 0.0;
    for(new i = 0; i < sizeof(gRegSkins[][]); i++) {
        if(gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][i]) {
            count_skins++;
        }
    }
    SetPVarInt(playerid, pVar__SelectSkin_MaxPage, floatround(count_skins / MAX_SKIN_ON_PAGE, floatround_ceil));

    if(GetPVarInt(playerid, pVar__SelectSkin_MaxPage) - value < 1) {
        TextDrawHideForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT]);
        TextDrawHideForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT]);
    } else {
        TextDrawShowForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT]);
        TextDrawShowForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_TEXT_NEXT]);
    }

    if(value <= 1) {
        TextDrawHideForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV]);
        TextDrawHideForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV]);
    } else {
        TextDrawShowForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV]);
        TextDrawShowForPlayer(playerid, gSelectSkinGTextDraw[SELECT_SKIN_TEXT_PREV]);
    }

    for(new slot, slot_x, slot_y; slot < MAX_SKIN_ON_PAGE; slot++) {
        new currect_pages = ((MAX_SKIN_ON_PAGE * value) - MAX_SKIN_ON_PAGE) + slot;
        if(!gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][currect_pages])
            continue;

        pTextDrawSelectSkin[playerid][slot] =
        CreatePlayerTextDraw            (playerid, 134.5 + (slot_x * SKIN_SELECT_SPACE_SLOT_X), 150.7 + (slot_y * SKIN_SELECT_SPACE_SLOT_Y), !"_");
        PlayerTextDrawTextSize          (playerid, pTextDrawSelectSkin[playerid][slot], 31.0, 31.0);
        PlayerTextDrawColor             (playerid, pTextDrawSelectSkin[playerid][slot], -1);
        PlayerTextDrawFont              (playerid, pTextDrawSelectSkin[playerid][slot], 5);
        PlayerTextDrawSetPreviewModel   (playerid, pTextDrawSelectSkin[playerid][slot], gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][currect_pages]);
        PlayerTextDrawSetSelectable     (playerid, pTextDrawSelectSkin[playerid][slot], true);
        PlayerTextDrawShow 			    (playerid, pTextDrawSelectSkin[playerid][slot]);

        if( ++ slot_x >= MAX_SKIN_ON_PAGE - 2) {
            slot_x = 0;
            slot_y ++;
        }
    }
}

stock DestroyTextDrawSkinSelect(playerid) {
    for(new slot; slot < MAX_SKIN_ON_PAGE; slot++) {
        PlayerTextDrawDestroy(playerid, pTextDrawSelectSkin[playerid][slot]);
        pTextDrawSelectSkin[playerid][slot] = PlayerText: INVALID_TEXT_DRAW;
    }
}

stock ChCreate_PlayerClickTextDraw(playerid, Text:clickedid) {
    if(_:clickedid == INVALID_TEXT_DRAW) {
        if(GetPVarInt(playerid, pVar__SelectSkin)) {
            SelectTextDraw(playerid, COLOR_GREY);
        }
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_NEXT]) {
        new page = GetPVarInt(playerid, pVar__SelectSkin_Page);
        page++;

        SetPVarInt(playerid, pVar__SelectSkin_Page, page);

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, page);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_PREV]) {
        new page = GetPVarInt(playerid, pVar__SelectSkin_Page);
        page--;

        SetPVarInt(playerid, pVar__SelectSkin_Page, page);

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, page);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_EUROPEAN]) {
        if(player_info[playerid][p_National] == PLAYER_NATIONAL_EUROPEAN)
            return 1;

        player_info[playerid][p_National] = PLAYER_NATIONAL_EUROPEAN;
        player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
        SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
        ApplyAnimation(
            playerid,
            !"CLOTHES", !"CLO_POSE_LOOP",
            4.1, true, false, false, false, 0, false
        );

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        new page = GetPVarInt(playerid, pVar__SelectSkin_Page);
        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, page);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_AFROAMERICAN]) {
        if(player_info[playerid][p_National] == PLAYER_NATIONAL_AFRO_AMERICAL)
            return 1;

        player_info[playerid][p_National] = PLAYER_NATIONAL_AFRO_AMERICAL;
        player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
        SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
        ApplyAnimation(
            playerid,
            !"CLOTHES", !"CLO_POSE_LOOP",
            4.1, true, false, false, false, 0, false
        );

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        SetPVarInt(playerid, pVar__SelectSkin_Page, 1);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, 1);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_LATINOS]) {
        if(player_info[playerid][p_National] == PLAYER_NATIONAL_LATINOS)
            return 1;

        player_info[playerid][p_National] = PLAYER_NATIONAL_LATINOS;
        player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
        SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
        ApplyAnimation(
            playerid,
            !"CLOTHES", !"CLO_POSE_LOOP",
            4.1, true, false, false, false, 0, false
        );

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        SetPVarInt(playerid, pVar__SelectSkin_Page, 1);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, 1);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_ASIAN]) {
        if(player_info[playerid][p_National] == PLAYER_NATIONAL_ASIAN)
            return 1;

        player_info[playerid][p_National] = PLAYER_NATIONAL_ASIAN;
        player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
        SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
        ApplyAnimation(
            playerid,
            !"CLOTHES", !"CLO_POSE_LOOP",
            4.1, true, false, false, false, 0, false
        );

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        SetPVarInt(playerid, pVar__SelectSkin_Page, 1);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, 1);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_MALE]) {
        if(player_info[playerid][p_Sex] == PLAYER_SEX_MALE)
            return 1;

        player_info[playerid][p_Sex] = PLAYER_SEX_MALE;
        player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
        SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
        ApplyAnimation(
            playerid,
            !"CLOTHES", !"CLO_POSE_LOOP",
            4.1, true, false, false, false, 0, false
        );

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        SetPVarInt(playerid, pVar__SelectSkin_Page, 1);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, 1);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_FEMALE]) {
        if(player_info[playerid][p_Sex] == PLAYER_SEX_FEMALE)
            return 1;

        player_info[playerid][p_Sex] = PLAYER_SEX_FEMALE;
        player_info[playerid][p_Skin] = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][0];
        SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
        ApplyAnimation(
            playerid,
            !"CLOTHES", !"CLO_POSE_LOOP",
            4.1, true, false, false, false, 0, false
        );

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        SetPVarInt(playerid, pVar__SelectSkin_Page, 1);

        DestroyTextDrawSkinSelect(playerid);
		CreatePlayerTextDrawSkin(playerid, 1);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS] || clickedid == gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_ANIMS]) {
        if(GetPVarInt(playerid, pVar__AntiFlood_Anims) > gettime()) {
            return 1;
        }

        if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_ANIMS]) {
            if(player_info[playerid][p_StyleChat] <= 0)
                return 1;

            player_info[playerid][p_StyleChat]--;
        } else {
            if(player_info[playerid][p_StyleChat] >= MAX_STYLE_CHAT_COUNT)
                return 1;

            player_info[playerid][p_StyleChat]++;
        }

        SetPVarInt(playerid, pVar__AntiFlood_Anims, gettime() + 6);

        switch(player_info[playerid][p_StyleChat]) {
            case 0: ApplyAnimation(playerid, !"PED", !"IDLE_CHAT", 4.1, 0, 1, 1, 1, 1, 1);
            case 1: ApplyAnimation(playerid, !"LOWRIDER", !"prtial_gngtlkH", 4.1, 0, 1, 1, 1, 1, 1);
            case 2: ApplyAnimation(playerid, !"GANGS", !"prtial_gngtlkB", 4.1, 0, 1, 1, 1, 1, 1);
        }
        pTimerClearAnims[playerid] = SetTimerEx(!"PlayerClearAnimation", 4500, false, !"i", playerid);
        SetPlayerFacingAngle(playerid, 220.0);

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);
        
        new str[18];
        format(
            str, sizeof(str),
            "ЖЕСТИКУЛЯЦИЯ_%d",
            player_info[playerid][p_StyleChat] + 1
        );

        PlayerTextDrawHide(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT]);
        PlayerTextDrawSetString(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT], str);
        PlayerTextDrawShow(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT]);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE] || clickedid == gSelectSkinGTextDraw[SELECT_SKIN_R_ARROWS_AGE]) {
        if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_L_ARROWS_AGE]) {
            if(player_info[playerid][p_Age] <= MIN_PLAYER_AGE)
                return 1;

            player_info[playerid][p_Age]--;
        } else {
            if(player_info[playerid][p_Age] >= MAX_PLAYER_AGE)
                return 1;

            player_info[playerid][p_Age]++;
        }

        PlayerPlaySound(playerid, 17803, 0.0, 0.0, 0.0);

        new str[18];
        format(
            str, sizeof(str),
            "ВОЗРАСТ_%d",
            player_info[playerid][p_Age]
        );

        PlayerTextDrawHide(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE]);
        PlayerTextDrawSetString(playerid,pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE], str);
        PlayerTextDrawShow(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE]);
    }

    if(clickedid == gSelectSkinGTextDraw[SELECT_SKIN_BG_FINISH]) {
        Dialog_Create(playerid, Dialog:Registration_PlayerSkinSelect);
    }
    return 1;
}

stock ChCreate_PlayerClickPTextDraw(playerid, PlayerText:playertextid) {
    if(GetPVarInt(playerid, pVar__SelectSkin)) {
        for(new i = 0; i < MAX_SKIN_ON_PAGE; i++) {
            if(playertextid == pTextDrawSelectSkin[playerid][i]) {
                if(GetPVarInt(playerid, pVar__AntiFlood_Skin) > gettime()) {
                    return 1;
                }

                new 
                    page = GetPVarInt(playerid, pVar__SelectSkin_Page),
                    currect_pages =  ((MAX_SKIN_ON_PAGE * page) - MAX_SKIN_ON_PAGE) + i,
                    currect_skin = gRegSkins[player_info[playerid][p_National]][player_info[playerid][p_Sex]][currect_pages]
                ;
                
                if(GetPlayerSkin(playerid) == currect_skin) {
                    return 1;
                }

                player_info[playerid][p_Skin] = currect_skin;

                SetPVarInt(playerid, pVar__AntiFlood_Skin, gettime() + 2);
                SetPlayerSkin(playerid, currect_skin);

                PlayerPlaySound(playerid, 20802, 0.0, 0.0, 0.0);

                SetPlayerFacingAngle(playerid, 180.0);

                if(pTimerClearAnims[playerid] != INVALID_PLAYER_TIMER_ID) {
                    KillTimer(pTimerClearAnims[playerid]);

                    #if DEBUG_MODE
                        printf("[KillTimer 1 SKIN] pTimerClearAnims[playerid] = '%d' killed",
                            pTimerClearAnims[playerid]
                        );
                    #endif

                    pTimerClearAnims[playerid] = INVALID_PLAYER_TIMER_ID;
                }

                ApplyAnimation(
                    playerid,
                    !"CLOTHES", !"CLO_POSE_LOOP",
                    4.1, true, false, false, false, 0, false
                );
            }
        }
    }
    return 1;   
}

dialog Registration_PlayerSkinSelect(playerid) {
    Create:<" "> {
        MessageBox:<"\n\n"#C_W"Вы действительно хотите выбрать данную {abcdef}одежду"#C_W"?\n\n"> {
            ResponseRight: {
                return DIALOG_CLOSE;
            }

            Create:<""#C_B"Регистрация | "#C_W"Создание персонажа"> {
                ResponseRight: {
                    return DIALOG_BACK;
                }

                Input:<"\
                    "#C_W"Введите имя вашего персонажа:\n\n\
                    "#C_G"Формат: Name_Surname\
                "> {

                    new name[MAX_PLAYER_NAME + 1];
                    Dialog_Text(playerid, name);

                    static const
                        fmt_query_find_name[] = "\
                            SELECT \
                                Name \
                            FROM \
                                "#MYSQL_TABLE_CHARACTER" \
                            WHERE \
                                Name = '%e'\
                            LIMIT 1";

                    new 
                        query[sizeof(fmt_query_find_name) + (-2 + MAX_PLAYER_NAME)],
                        deepid = Dialog_GetDeep(playerid)
                    ;
                    mysql_format(
                        dbHandle, query, sizeof(query), 
                        fmt_query_find_name, 
                        name
                    );
                    DialogQuery:<dbHandle, query>;
                    if(cache_num_rows()) {
                        PlayerClearChat(playerid);
                        SendErrorMessage(playerid, "Данное имя персонажа занято!");
                        Dialog_CacheDestroy(playerid, deepid);
                        return DialogGoto:<deepid>;
                    }

                    if(!textlen(name, 6, MAX_PLAYER_NAME)) {
                        PlayerClearChat(playerid);
                        SendErrorMessage(playerid, "Введите имя в формате: Name_Surname. Длина от 6 до 24-х символов");
                        Dialog_CacheDestroy(playerid, deepid);
                        return DialogGoto:<deepid>;
                    }

                    new Regex:NAME_CHECK = Regex_New("^[a-zA-Z]{1,10}_[a-zA-Z]{1,10}$");
                    if(Regex_Check(name, NAME_CHECK)) {  
                        PlayerClearChat(playerid);

                        strmid(player_info[playerid][p_Name], name, 0, MAX_PLAYER_NAME, MAX_PLAYER_NAME);

                        DeletePVar(playerid, pVar__SelectSkin);
                        DeletePVar(playerid, pVar__SelectSkin_Page);
                        DeletePVar(playerid, pVar__SelectSkin_MaxPage);
                        DeletePVar(playerid, pVar__AntiFlood_Skin);
                        DeletePVar(playerid, pVar__AntiFlood_Anims);

                        DestroyTextDrawSkinSelect(playerid);
                        CancelSelectTextDraw(playerid);

                        PlayerTextDrawDestroy(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT]);
                        pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_STYLE_CHAT] = PlayerText: INVALID_TEXT_DRAW;

                        PlayerTextDrawDestroy(playerid, pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE]);
                        pTextDrawSelectAge[playerid][P_SKIN_SELECT_TEXT_AGE] = PlayerText: INVALID_TEXT_DRAW;

                        for(new i = 0; i < MAX_SELECT_SKIN_GTEXTDAWS; i++) {
                            TextDrawHideForPlayer(playerid, gSelectSkinGTextDraw[i]);
                        }

                        SetPlayerLogged(playerid, true);
                        temp_info[playerid][tRequest] = false;

                        CreateNewAccount(playerid);
                    } else {
                        PlayerClearChat(playerid);
                        Regex_Delete(NAME_CHECK);

                        SendErrorMessage(playerid, "Введите имя в формате: Name_Surname");
                        
                        Dialog_CacheDestroy(playerid, deepid);
						return DialogGoto:<deepid>;
                    }
                    Regex_Delete(NAME_CHECK);
                }
            }
            Button:<"Создать", "Назад">;
        }
    }
    Button:<"Выбрать", "X">;
}

stock CreateInteriorSelectSkin(playerid) {
    pObjectsPlayerSelectSkin[playerid][0] = CreateDynamicObject(19379, -2238.523925, 1250.101928, 86.566398, 0.000000, 90.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][0], 0, 18029, !"genintintsmallrest", !"GB_restaursmll13", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][1] = CreateDynamicObject(19445, -2234.086425, 1254.794555, 88.387199, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][1], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][2] = CreateDynamicObject(19445, -2243.677734, 1245.803100, 88.387199, 0.000000, 0.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][2], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][3] = CreateDynamicObject(19445, -2243.679687, 1250.063110, 85.405197, 0.000000, 0.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][3], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][4] = CreateDynamicObject(19445, -2238.949462, 1254.792602, 85.407203, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][4], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][5] = CreateDynamicObject(19445, -2243.679687, 1250.063110, 91.271202, 0.000000, 0.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][5], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][6] = CreateDynamicObject(19445, -2238.949462, 1254.792602, 85.407203, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][6], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][7] = CreateDynamicObject(19445, -2238.949462, 1254.792602, 91.272201, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][7], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][8] = CreateDynamicObject(1897, -2243.692382, 1251.733764, 87.047096, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][8], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][9] = CreateDynamicObject(1897, -2243.694335, 1253.736816, 87.045097, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][9], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][10] = CreateDynamicObject(1897, -2242.541992, 1254.777465, 87.043098, 90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][10], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][11] = CreateDynamicObject(1897, -2240.307861, 1254.777465, 87.043098, 90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][11], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][12] = CreateDynamicObject(1897, -2238.073974, 1254.777465, 87.043098, 90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][12], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][13] = CreateDynamicObject(1897, -2243.692382, 1250.515747, 88.181098, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][13], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][12] = CreateDynamicObject(1897, -2243.692382, 1250.515747, 90.413101, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][12], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][13] = CreateDynamicObject(1897, -2243.692382, 1251.733764, 89.435096, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][13], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][14] = CreateDynamicObject(1897, -2243.694335, 1253.736816, 89.623100, -90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][14], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][15] = CreateDynamicObject(1897, -2242.541992, 1254.777465, 89.624099, -90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][15], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][16] = CreateDynamicObject(1897, -2240.307861, 1254.777465, 89.623100, -90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][16], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][17] = CreateDynamicObject(1897, -2238.073974, 1254.777465, 89.433097, 90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][17], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][18] = CreateDynamicObject(1897, -2238.802001, 1254.777465, 88.273101, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][18], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][19] = CreateDynamicObject(1897, -2238.802001, 1254.777465, 90.508102, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][19], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][20] = CreateDynamicObject(19459, -2243.667236, 1249.871459, 84.942100, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][20], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][21] = CreateDynamicObject(19459, -2238.774414, 1254.777465, 84.942100, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][21], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][22] = CreateDynamicObject(19459, -2243.667236, 1249.871459, 91.758102, 180.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][22], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][23] = CreateDynamicObject(19459, -2238.774414, 1254.777465, 91.758102, 180.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][23], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][24] = CreateDynamicObject(19378, -2238.517578, 1250.062744, 90.160301, 0.000000, 90.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][24], 0, 18029, !"genintintsmallrest", !"GB_restaursmll13", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][25] = CreateDynamicObject(2189, -2238.035888, 1250.016357, 86.670097, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][25], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0x00000000);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][25], 1, 14581, !"ab_mafiasuitea", !"cof_wood2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][26] = CreateDynamicObject(19328, -2243.587890, 1249.347045, 88.185600, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][26], 0, 14742, !"mp3", !"GB_rapposter02", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][27] = CreateDynamicObject(18066, -2243.743408, 1249.331054, 89.264602, 90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][27], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][28] = CreateDynamicObject(18066, -2243.743408, 1249.331054, 87.092597, 90.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][28], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][29] = CreateDynamicObject(18066, -2243.724853, 1248.665039, 88.544601, 180.000000, 90.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][29], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][30] = CreateDynamicObject(18066, -2243.722900, 1248.665039, 87.762603, 180.000000, 90.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][30], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][31] = CreateDynamicObject(18066, -2243.724853, 1250.003051, 87.762603, 180.000000, 90.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][31], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][32] = CreateDynamicObject(18066, -2243.722900, 1250.005004, 88.544601, 180.000000, 90.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][32], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][33] = CreateDynamicObject(1818, -2243.290527, 1249.863159, 86.494201, 0.000000, 0.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][33], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][34] = CreateDynamicObject(11710, -2243.588623, 1250.288330, 87.258598, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][34], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][35] = CreateDynamicObject(11710, -2243.588623, 1250.288330, 88.338600, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][35], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][36] = CreateDynamicObject(2238, -2243.483642, 1250.316772, 87.716300, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][36], 0, 18029, "genintintsmallrest", "GB_restaursmll16b", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][37] = CreateDynamicObject(11710, -2243.590576, 1250.352416, 87.256599, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][37], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][38] = CreateDynamicObject(2238, -2243.483642, 1250.316772, 88.798301, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][38], 0, 1963, !"estateprops", !"grn_cyl_32", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][39] = CreateDynamicObject(11710, -2243.590576, 1250.352416, 88.340599, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][39], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][40] = CreateDynamicObject(19159, -2243.279296, 1249.306030, 87.158699, 0.000000, 180.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][40], 0, 19058, !"xmasboxes", !"wrappingpaper28", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][41] = CreateDynamicObject(1945, -2243.281005, 1249.298339, 86.999198, 90.000000, 127.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][41], 0, 19627, !"wrench1", !"wrench1", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][42] = CreateDynamicObject(2484, -2237.853759, 1254.609985, 88.980598, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][42], 0, 19339, !"coffin01", !"coffin_top01", 0xFFFFFFFF);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][42], 2, 10101, !"2notherbuildsfe", !"Bow_Abpave_Gen", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][43] = CreateDynamicObject(2828, -2243.212158, 1249.933227, 86.999298, 0.000000, 0.000000, -135.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][43], 0, 16644, !"a51_detailstuff", !"roucghstonebrtb", 0x00000000);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][43], 1, 16644, !"a51_detailstuff", !"roucghstonebrtb", 0x00000000);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][43], 2, 16644, !"a51_detailstuff", !"roucghstonebrtb", 0x00000000);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][43], 3, 16644, !"a51_detailstuff", !"roucghstonebrtb", 0x00000000);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][43], 5, 2266, !"picture_frame", !"CJ_PAINTING7", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][44] = CreateDynamicObject(1763, -2238.413818, 1254.177978, 86.654197, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][44], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0xFFFFFFFF);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][44], 1, 14581, !"ab_mafiasuitea", !"cof_wood2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][45] = CreateDynamicObject(1744, -2238.289062, 1254.903808, 87.872398, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][45], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][46] = CreateDynamicObject(1744, -2238.289062, 1254.903808, 87.838401, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][46], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][47] = CreateDynamicObject(1734, -2239.690185, 1251.137817, 90.075698, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][47], 0, 1929, !"kbroul2", !"roul_slotbit6", 0x00000000);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][47], 1, 15046, !"svcunthoose", !"mplid02", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][48] = CreateDynamicObject(2205, -2241.256103, 1254.202636, 86.654296, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][48], 0, 14581, !"ab_mafiasuitea", !"cof_wood2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][49] = CreateDynamicObject(19808, -2240.627929, 1254.152954, 87.603797, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][49], 0, 11631, !!"mp_ranchcut", !"mpcj_speaker_6", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][50] = CreateDynamicObject(2263, -2240.637695, 1253.944335, 87.653701, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][50], 0, 19894, !"laptopsamp1", !"laptopscreen2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][51] = CreateDynamicObject(2263, -2240.601562, 1254.948242, 87.653701, 0.000000, 0.000000, 180.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][51], 0, 19894, !"laptopsamp1", !"laptopscreen2", 0xFF000000);
    pObjectsPlayerSelectSkin[playerid][52] = CreateDynamicObject(11711, -2240.606201, 1254.497192, 87.775299, 0.000000, 90.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][52], 0, 18632, !"fishingrod", !"rodpole2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][53] = CreateDynamicObject(19568, -2240.607910, 1254.477294, 87.462196, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][53], 0, 18632, !"fishingrod", !"rodpole2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][54] = CreateDynamicObject(19874, -2240.116943, 1254.185546, 87.590202, 0.000000, 0.000000, -80.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][54], 0, 11631, !!"mp_ranchcut", !"mpcj_speaker_6", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][55] = CreateDynamicObject(19569, -2241.071777, 1254.499633, 87.575302, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][55], 0, 11631, !!"mp_ranchcut", !"mpCJ_SPEAKER4", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][56] = CreateDynamicObject(19569, -2240.154785, 1254.499633, 87.575302, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][56], 0, 11631, !!"mp_ranchcut", !"mpCJ_SPEAKER4", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][57] = CreateDynamicObject(1924, -2240.163818, 1254.446411, 87.660102, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][57], 0, 11631, !"mp_ranchcut", !"mpcj_speaker2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][58] = CreateDynamicObject(1924, -2240.163818, 1254.446411, 87.735099, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][58], 0, 11631, !"mp_ranchcut", !"mpcj_speaker2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][59] = CreateDynamicObject(1924, -2241.081787, 1254.446411, 87.660102, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][59], 0, 11631, !"mp_ranchcut", !"mpcj_speaker2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][60] = CreateDynamicObject(1924, -2241.081787, 1254.446411, 87.735099, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][60], 0, 11631, !"mp_ranchcut", !"mpcj_speaker2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][61] = CreateDynamicObject(19614, -2240.112060, 1254.242309, 86.654899, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][61], 0, 11631, !"mp_ranchcut", "mpcj_speaker_6", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][62] = CreateDynamicObject(19565, -2240.037597, 1254.175170, 86.857299, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][62], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][63] = CreateDynamicObject(18641, -2240.129882, 1254.099609, 86.792999, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][63], 0, 8409, !"gnhotel1", !"redstuff", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][64] = CreateDynamicObject(19828, -2240.184570, 1253.996337, 87.086997, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][64], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][65] = CreateDynamicObject(19828, -2240.184570, 1253.996337, 87.033996, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][65], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][66] = CreateDynamicObject(19828, -2240.184570, 1253.996337, 86.981002, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][66], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][67] = CreateDynamicObject(19828, -2240.184570, 1253.996337, 86.928001, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][67], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][68] = CreateDynamicObject(19896, -2240.207275, 1253.945556, 86.711097, 0.000000, 90.000000, -90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][68], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][69] = CreateDynamicObject(19896, -2240.097167, 1253.945556, 86.711097, 0.000000, 90.000000, -90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][69], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][70] = CreateDynamicObject(19896, -2240.067138, 1253.943603, 86.711097, 0.000000, 90.000000, -90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][70], 0, 15046, !"svcunthoose", !"csGarageTrolley01psd", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][71] = CreateDynamicObject(18644, -2240.213623, 1253.983642, 86.711700, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][71], 0, 18632, !"fishingrod", !"rodpole2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][72] = CreateDynamicObject(18644, -2240.128662, 1253.981689, 86.711700, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][72], 0, 18632, !"fishingrod", !"rodpole2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][73] = CreateDynamicObject(18644, -2240.048583, 1253.981689, 86.711700, 90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][73], 0, 18632, !"fishingrod", !"rodpole2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][74] = CreateDynamicObject(2685, -2240.131835, 1254.137695, 87.613800, -90.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][74], 0, 18632, !"fishingrod", !"rodpole2", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][75] = CreateDynamicObject(1714, -2240.799560, 1253.108886, 86.638397, 0.000000, 0.000000, 142.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][75], 0, -1, !"none", !"none", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][76] = CreateDynamicObject(1946, -2239.154541, 1254.203491, 86.861099, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][76], 0, -1, !"none", !"none", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][77] = CreateDynamicObject(2891, -2238.730712, 1254.296875, 87.211898, 0.000000, 52.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][77], 0, 14383, !"burg_1", !"carpet4kb", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][78] = CreateDynamicObject(1759, -2243.007568, 1250.932250, 86.654098, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][78], 0, 9515, !"bigboxtemp1", !"ws_alley5_256_blank", 0xFFFFFFFF);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][78], 1, 14581, !"ab_mafiasuitea", !"cof_wood2", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][79] = CreateDynamicObject(2891, -2243.032470, 1251.879638, 87.211898, 0.000000, 52.000000, -90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][79], 0, 14383, !"burg_1", !"carpet4kb", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][80] = CreateDynamicObject(2011, -2243.088378, 1254.292602, 86.653816, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][80], 0, -1, !"none", !"none", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][81] = CreateDynamicObject(3858, -2236.381103, 1254.774414, 87.175003, 0.000000, 0.000000, 45.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][81], 0, 3902, !"libertyhi3", !"glass2_64", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][82] = CreateDynamicObject(3858, -2243.673828, 1247.486938, 87.175003, 0.000000, 0.000000, 135.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][82], 0, 3902, !"libertyhi3", !"glass2_64", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][83] = CreateDynamicObject(19843, -2239.704345, 1251.173095, 90.059700, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][83], 0, 10101, !"2notherbuildsfe", !"sl_vicwall02", 0xFFFFFFFF);
    pObjectsPlayerSelectSkin[playerid][84] = CreateDynamicObject(19433, -2243.765136, 1250.813842, 88.697746, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][84], 0, 11388, !"newhubgrg1_sfse", !"ws_hubbeams1", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][85] = CreateDynamicObject(19433, -2239.261474, 1254.832885, 88.697799, 0.000000, 0.000000, 90.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][85], 0, 11388, !"newhubgrg1_sfse", !"ws_hubbeams1", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][86] = CreateDynamicObject(1734, -2239.880859, 1250.931884, 90.483703, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][86], 0, 1929, !"kbroul2", !"roul_slotbit6", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][87] = CreateDynamicObject(1734, -2239.494140, 1251.344726, 90.483703, 0.000000, 0.000000, 0.000000, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][87], 0, 1929, !"kbroul2", !"roul_slotbit6", 0x00000000);
    pObjectsPlayerSelectSkin[playerid][88] = CreateDynamicObject(2196, -2240.913574, 1254.362548, 87.580932, 0.000000, 0.000000, -52.299999, playerid + 3);
    SetDynamicObjectMaterial(pObjectsPlayerSelectSkin[playerid][88], 0, -1, !"none", !"none", 0xFFFFFFFF);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    pObjectsPlayerSelectSkin[playerid][89] = CreateDynamicObject(2194, -2243.310302, 1248.816406, 87.278800, 0.000000, 0.000000, 0.000000, playerid + 3);
    pObjectsPlayerSelectSkin[playerid][90] = CreateDynamicObject(1923, -2243.241455, 1249.073974, 86.999557, 0.000000, 0.000000, 0.000000, playerid + 3);
    pObjectsPlayerSelectSkin[playerid][91] = CreateDynamicObject(1923, -2243.190917, 1249.147583, 86.999557, 0.000000, 0.000000, 0.000000, playerid + 3);
    pObjectsPlayerSelectSkin[playerid][92] = CreateDynamicObject(1923, -2243.162597, 1249.062622, 86.999557, 0.000000, 0.000000, 0.000000, playerid + 3);
}

stock DestroyInteriorSelectSkin(playerid) {
    for(new i = 0; i < sizeof(pObjectsPlayerSelectSkin[]); i++) {
        if(IsValidDynamicObject(pObjectsPlayerSelectSkin[playerid][i])) {
            DestroyDynamicObject(pObjectsPlayerSelectSkin[playerid][i]);
            pObjectsPlayerSelectSkin[playerid][i] = INVALID_OBJECT_ID;
        }
    }
}