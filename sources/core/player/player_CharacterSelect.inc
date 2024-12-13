#define MAX_PLAYER_CHARACTER_AMOUNT 3
#define CHARACTER_SPACE_Y_PTD       25

enum {
    PlayerText: CHARACTER_SELECT_PTD_NAME,
    PlayerText: CHARACTER_SELECT_PTD_HOURS,
    MAX_CHARACTER_SELECT_PTD
}

enum {
    PlayerText: CHARACTER_SELECT_PTD_BG[MAX_PLAYER_CHARACTER_AMOUNT],
    PlayerText: CHARACTER_SELECT_PTD_BG_1[MAX_PLAYER_CHARACTER_AMOUNT],
    PlayerText: CHARACTER_SELECT_PTD_NAME_1[MAX_PLAYER_CHARACTER_AMOUNT],
    MAX_CHARACTERS_PTD
}

new 
    pLoadingsID[MAX_PLAYERS][MAX_PLAYER_CHARACTER_AMOUNT],
    PlayerText: pCharacterSelectPTD[MAX_PLAYERS][MAX_CHARACTER_SELECT_PTD],
    PlayerTexT: pCharactersPTD[MAX_PLAYERS][MAX_CHARACTERS_PTD],
    pVar__SelectCharacterTD[] = !"pVar__SelectCharacterTD",
    pVar__SelectCharaterID[] = !"pVar__SelectCharaterID"
;

public: OnPlayerSelectCharacter(playerid) {
    new rows;
    cache_get_row_count(rows);

    if(!rows) {
        printf(">> !! ОШИБКА ВЫБОРА ПЕРСОНАЖА: ПЕРСОНАЖ %s НЕ НАЙДЕН! [MYSQL_ERROR_SELECT_PLAYER_CHARACTER]", player_info[playerid][p_Name]);
        SendErrorMessage(playerid, "Произошла ошибка [MYSQL_ERROR_SELECT_PLAYER_CHARACTER]. Напишите проблему в технический раздел на форуме, приложив данную ошибку");
        Kick(playerid);
        return 1;
    }

    new
        hour_player,
        minute_player
    ;
    gettime(hour_player,minute_player);
    SetPlayerTime(playerid, hour_player, minute_player);

    cache_get_value_name_int(0, !"Skin", player_info[playerid][p_Skin]);
    SetPlayerSkin(playerid, player_info[playerid][p_Skin]);

    TogglePlayerControllable(playerid, false);
    SetPVarInt(playerid, pVar__SelectCharacterTD, 1);

    for(new i = 0; i < rows; i++) {
        if(i > MAX_PLAYER_CHARACTER_AMOUNT - 1) {
            printf(">> У логина %s [user_id:%d] больше "#MAX_PLAYER_CHARACTER_AMOUNT" персонажей....", account_info[playerid][account_Login], account_info[playerid][account_ID]);
            SendErrorMessage(playerid, "У вас больше "#MAX_PLAYER_CHARACTER_AMOUNT" персонажей. Были загружены первые "#MAX_PLAYER_CHARACTER_AMOUNT". Вы можете написать администрации насчет этой проблемы, и удалить ненужных персонажей, если это необходимо");
            break;
        }

        new 
            temp_ID,
            temp_name[MAX_PLAYER_NAME + 1]
        ;  

        cache_get_value_name_int(i, !"ID", temp_ID);

        cache_get_value_name(i, !"NameUP", temp_name, MAX_PLAYER_NAME);

        pLoadingsID[playerid][i] = temp_ID;

        printf(">> %s Найден персонаж ID: %d [%d]", temp_name, pLoadingsID[playerid][i], i);

        pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i] = 
        CreatePlayerTextDraw            (playerid, 147.0, 201.0 + (i * CHARACTER_SPACE_Y_PTD), !"LD_SPAC:white"); // пусто
        PlayerTextDrawTextSize          (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i], 69.0, 24.0);
        PlayerTextDrawColor             (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i], 255);
        PlayerTextDrawFont              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i], 4);
        PlayerTextDrawShow              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i]);

        pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i] = 
        CreatePlayerTextDraw            (playerid, 148.0, 203.0 + (i * CHARACTER_SPACE_Y_PTD), !"LD_SPAC:white"); // пусто
        PlayerTextDrawTextSize          (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i], 67.0, 20.0);
        PlayerTextDrawColor             (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i], (i == 0) ? (COLOR_DIMGRAY) : (-1061109505));
        PlayerTextDrawFont              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i], 4);
        PlayerTextDrawShow              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i]);

        pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i] = 
        CreatePlayerTextDraw            (playerid, 180.0, 207.0 + (i * CHARACTER_SPACE_Y_PTD), temp_name); // пусто
        PlayerTextDrawLetterSize        (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i], 0.1, 1.2);
        PlayerTextDrawTextSize          (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i], 9.0, 68.0);
        PlayerTextDrawAlignment         (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i], 2);
        PlayerTextDrawColor             (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i], 255);
        PlayerTextDrawSetShadow         (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i], 0);
        PlayerTextDrawSetSelectable     (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i], true);
        PlayerTextDrawShow              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i]);
    }

    if(rows < MAX_PLAYER_CHARACTER_AMOUNT) {
        pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][rows] = 
        CreatePlayerTextDraw            (playerid, 147.0, 201.0 + (rows * CHARACTER_SPACE_Y_PTD), !"LD_SPAC:white"); // пусто
        PlayerTextDrawTextSize          (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][rows], 69.0, 24.0);
        PlayerTextDrawColor             (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][rows], 255);
        PlayerTextDrawFont              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][rows], 4);
        PlayerTextDrawShow              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][rows]);

        pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][rows] = 
        CreatePlayerTextDraw            (playerid, 148.0, 203.0 + (rows * CHARACTER_SPACE_Y_PTD), !"LD_SPAC:white"); // пусто
        PlayerTextDrawTextSize          (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][rows], 67.0, 20.0);
        PlayerTextDrawColor             (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][rows], 3368703);
        PlayerTextDrawFont              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][rows], 4);
        PlayerTextDrawShow              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][rows]);

        pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows] = 
        CreatePlayerTextDraw            (playerid, 180.0, 207.0 + (rows * CHARACTER_SPACE_Y_PTD), !"НОВЫЙ_ПЕРСОНАЖ"); // пусто
        PlayerTextDrawLetterSize        (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows], 0.1, 1.2);
        PlayerTextDrawTextSize          (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows], 9.0, 68.0);
        PlayerTextDrawAlignment         (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows], 2);
        PlayerTextDrawColor             (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows], -1061109505);
        PlayerTextDrawSetShadow         (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows], 0);
        PlayerTextDrawSetSelectable     (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows], true);
        PlayerTextDrawShow              (playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][rows]);
    }

    for(new i; i < MAX_CHARACTER_SELECT_GTEXTDRAWS; i++) {
        TextDrawShowForPlayer(playerid, gCharacterSelectGTextDraw[i]);
    }

    pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME] = 
    CreatePlayerTextDraw        (playerid, 214.0, 184.0, account_info[playerid][account_Login]); // пусто
    PlayerTextDrawLetterSize    (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME], 0.1, 0.8);
    PlayerTextDrawAlignment     (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME], 3);
    PlayerTextDrawColor         (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME], -1061109505);
    PlayerTextDrawSetShadow     (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME], 0);

    PlayerTextDrawShow(playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME]);

    new 
        str[15],
        hour = (account_info[playerid][account_LastDateUnix] - account_info[playerid][account_RegDateUnix]) / UNIX_HOUR
    ;
    format(
        str, sizeof(str),
        "%d_%s",
        hour,
        PluralToText(hour, "ЧАС", "ЧАСА", "ЧАСОВ")
    );

    pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS] = 
    CreatePlayerTextDraw        (playerid, 214.0, 192.0, str); // пусто
    PlayerTextDrawLetterSize    (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS], 0.1, 0.6);
    PlayerTextDrawAlignment     (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS], 3);
    PlayerTextDrawColor         (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS], -1061109505);
    PlayerTextDrawSetShadow     (playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS], 0);
    PlayerTextDrawShow(playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS]);

    SelectTextDraw(playerid, COLOR_LIGHTGRAY);

    SetPVarInt(playerid, pVar__SelectCharaterID, pLoadingsID[playerid][0]);
    return 1;
}

stock Character_PlayerClickTextDraw(playerid, Text:clickedid) {
    if(_:clickedid == INVALID_TEXT_DRAW) {
        if(GetPVarInt(playerid, pVar__SelectCharacterTD)) {
            SelectTextDraw(playerid, COLOR_LIGHTGRAY);
        }
    }

    if(clickedid == gCharacterSelectGTextDraw[CHARACTER_SELECT_TEXT_ENTER]) {
        DeletePVar(playerid, pVar__SelectCharacterTD);

        PlayerTextDrawDestroy(playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME]);
        pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_NAME] = PlayerText: INVALID_TEXT_DRAW;

        PlayerTextDrawDestroy(playerid, pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS]);
        pCharacterSelectPTD[playerid][CHARACTER_SELECT_PTD_HOURS] = PlayerText: INVALID_TEXT_DRAW;

        for(new i = 0; i < MAX_PLAYER_CHARACTER_AMOUNT; i++) {
            if(pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i] == PlayerText: INVALID_TEXT_DRAW)
                continue;

            PlayerTextDrawDestroy(playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i]);
            pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG][i] = PlayerText: INVALID_TEXT_DRAW;

            PlayerTextDrawDestroy(playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i]);
            pCharactersPTD[playerid][CHARACTER_SELECT_PTD_BG_1][i] = PlayerText: INVALID_TEXT_DRAW;

            PlayerTextDrawDestroy(playerid, pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i]);
            pCharactersPTD[playerid][CHARACTER_SELECT_PTD_NAME_1][i] = PlayerText: INVALID_TEXT_DRAW;
        }
        

        for(new i; i < MAX_CHARACTER_SELECT_GTEXTDRAWS; i++) {
            TextDrawHideForPlayer(playerid, gCharacterSelectGTextDraw[i]);
        }
        CancelSelectTextDraw(playerid);

        TogglePlayerBackground(playerid, 1000, CHARACTER_LOAD_BACKGROUND_ID);
    }
}

stock CharacterLoad_BackgroudUpdate(playerid, status) {
    if(status == BACKGROUND_STATUS_ON) {
        new character_id = GetPVarInt(playerid, pVar__SelectCharaterID);
        DeletePVar(playerid, pVar__SelectCharaterID);

        static const
            fmt_query[] = "\
            SELECT \
            *, \
                UNIX_TIMESTAMP(RegDateUnix) AS Regdate, \
                UNIX_TIMESTAMP(LastDateUnix) AS Lastdate \
            FROM \
                "#MYSQL_TABLE_CHARACTER" \
            WHERE \
                ID = '%i' \
            LIMIT 1";

        new query[sizeof(fmt_query) + (-2 + 11)];
        mysql_format(
            dbHandle, query, sizeof(query),
            fmt_query,
            character_id
        );
        mysql_tquery(
            dbHandle,
            query,
            !"OnPlayerLoadingCharacter",
            !"d",
            playerid
        );
    }
}