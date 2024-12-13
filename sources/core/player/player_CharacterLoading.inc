public: OnPlayerLoadingCharacter(playerid) {
    new rows;
    cache_get_row_count(rows);

    if(!rows) {
        SetPlayerLogged(playerid, false);
        temp_info[playerid][tRequest] = true;

        printf(">> !! ОШИБКА СОЗДАНИЯ ПЕРСОНАЖА: ПЕРСОНАЖ %s НЕ НАЙДЕН! [MYSQL_ERROR_REGISTRATION_PLAYER_CHARACTER]", player_info[playerid][p_Name]);
        SendErrorMessage(playerid, "Произошла ошибка [MYSQL_ERROR_REGISTRATION_PLAYER_CHARACTER]. Напишите проблему в технический раздел на форуме, приложив данную ошибку");
        Kick(playerid);
        return 1;
    }

    cache_get_value_name_int(0, !"ID", player_info[playerid][p_ID]);
    cache_get_value_name(0, !"Name", player_info[playerid][p_Name], MAX_PLAYER_NAME);
    cache_get_value_name_int(0, !"National", player_info[playerid][p_National]);
    cache_get_value_name_int(0, !"Sex", player_info[playerid][p_Sex]);
    cache_get_value_name_int(0, !"Money", player_info[playerid][p_Money]);
    cache_get_value_name_int(0, !"Lvl", player_info[playerid][p_Lvl]);
    cache_get_value_name_int(0, !"Exp", player_info[playerid][p_Exp]);
    cache_get_value_name_int(0, !"Age", player_info[playerid][p_Age]);
    cache_get_value_name_int(0, !"StyleChat", player_info[playerid][p_StyleChat]);
    cache_get_value_name_int(0, !"Skin", player_info[playerid][p_Skin]);
    cache_get_value_name_int(0, !"Regdate", player_info[playerid][p_RegDateUnix]);
    cache_get_value_name_int(0, !"Lastdate", player_info[playerid][p_LastDateUnix]);

    static const
        fmt_query[] = "\
        UPDATE \
            "#MYSQL_TABLE_USERS" \
        SET \
            Online = '1' \
        WHERE \
            ID = '%i' \
        LIMIT 1";

    new query[sizeof(fmt_query) + (-2 + MAX_IP_LENGHT) + (-2 + 11)];
    mysql_format(
        dbHandle, query, sizeof(query),
        fmt_query,
        account_info[playerid][account_ID]
    );
    mysql_tquery(dbHandle, query);

    static const
        fmt_query_character[] = "\
        UPDATE \
            "#MYSQL_TABLE_CHARACTER" \
        SET \
            LastDateUnix = CURRENT_TIMESTAMP \
        WHERE \
            ID = '%i' \
        LIMIT 1";

    new query_character[sizeof(fmt_query_character) + (-2 + 11)];
    mysql_format(
        dbHandle, query_character, sizeof(query_character),
        fmt_query_character,
        player_info[playerid][p_ID]
    );
    mysql_tquery(dbHandle, query_character);

    SetPlayerName(playerid, player_info[playerid][p_Name]);
    SetPlayerScore(playerid, player_info[playerid][p_Lvl]);

    GivePlayerMoney(playerid, player_info[playerid][p_Money]);

    temp_info[playerid][tRequest] = false;

    DeletePVar(playerid, pVar__Timer_Login);
    SetPlayerLogged(playerid, true);
    Iter_Add(ITER_pLogged, playerid);

    SpawnPlayer(playerid);

    PlayerClearChat(playerid);
    new 
        temp_date[25],
        str[48 + 25]
    ;
    cache_get_value_name(0, !"LastDateUnix", temp_date, sizeof(temp_date));
    format(
        str, sizeof(str),
        "Последний раз вы заходили на данного персонажа: %s",
        temp_date
    );
    SendClientMessage(playerid, COLOR_LGR, str);
    return 1;
}