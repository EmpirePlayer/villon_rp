#define MAX_MINUTE_REGISTRATION     10
#define MAX_MINUTE_LOGIN            2

new pVar__Timer_Login[] = !"pVar__Timer_Login";

#include    "account_register"
#include    "account_login"

stock Account_RequestClass(playerid) {
    if(!IsPlayerLogged(playerid)) {
        temp_info[playerid][tRequest] = true;
    }

    SetSpawnInfo(playerid, 255, 36, 0, 0, 0 + 4, 1.0, -1, -1, -1, -1, -1, -1);
	SpawnPlayer(playerid);
    return 1;
}

stock Account_Spawn(playerid) {
    #if DEBUG_MODE
        printf(
            "ACCOUNT_SPAWN: temp_info_tRequest: %d",
            temp_info[playerid][tRequest]
        );
    #endif

    if(temp_info[playerid][tRequest]) {
        SetPlayerPos(playerid, 2169.0073,2165.9534,10.8203);
        InterpolateCameraPos(playerid, 1995.7109,2135.8057, 82.1922, 2138.0286, 2145.0374, 47.7033, 8000);
        InterpolateCameraLookAt(playerid, 2138.0286,2145.0374,47.7033, 2163.7065,2157.8982,41.8413, 8000);
        SetPlayerVirtualWorld(playerid, playerid + 3);
        SetPlayerTime(playerid, 0, 0);

        static const
            fmt_query[] = "\
            SELECT \
                Online \
            FROM \
                "#MYSQL_TABLE_USERS" \
            WHERE \
                Login = '%e' \
            AND \
                Online = '1' \
            LIMIT 1";
        new query[sizeof(fmt_query) + (-2 + MAX_PLAYER_NAME)];
        mysql_format(
            dbHandle, query, sizeof(query),
            fmt_query,
            account_info[playerid][account_Login]
        );
        mysql_tquery(
            dbHandle, query,
            !"ACCOUNT_MYSQL_CHECK_ONLINE",
            !"d",
            playerid
        );

        PlayerClearChat(playerid);
        return 1;
    }

    if(!IsPlayerConnected(playerid) || !IsPlayerLogged(playerid)) {
        Kick(playerid);
        return SendErrorMessage(playerid, "Необходимо авторизироваться");
    }

    PlayerSettingsSpawn(playerid);
    return 1;
}

public: ACCOUNT_MYSQL_CHECK_ONLINE(playerid) {
    new rows;
    cache_get_row_count(rows);

    if(rows) {
        SendErrorMessage(playerid, "Данный логин находится онлайн на сервере");
        Kick(playerid);
        return 1;
    }

    static const
        fmt_query[] = "\
            SELECT \
                ID, Password, Salt \
            FROM \
                "#MYSQL_TABLE_USERS" \
            WHERE \
                Login = '%e' \
            LIMIT 1";
    new query[sizeof(fmt_query) + (-2 + MAX_PLAYER_NAME)];
    mysql_format(
        dbHandle, query, sizeof(query),
        fmt_query,
        account_info[playerid][account_Login]
    );
    mysql_tquery(
        dbHandle, query,
        !"ACCOUNT_MYSQL_CHECK",
        !"d",
        playerid
    );
    return 1;
}

public: ACCOUNT_MYSQL_CHECK(playerid) {
    if(IsPlayerNPC(playerid))
		return 1;

    new rows;
    cache_get_row_count(rows);

    if(!rows) {
        OnPlayerRegister(playerid);
    } else {
        OnPlayerLogin(playerid);
    }
    return 1;
}

stock PlayerTimerAccountLogin(playerid) {
    if(GetPVarInt(playerid, pVar__Timer_Login) <= gettime() && GetPVarInt(playerid, pVar__Timer_Login) != 0) {
        SendErrorMessage(playerid, "Вы были кикнуты за долгую регистрацию/авторизацию");
        DeletePVar(playerid, pVar__Timer_Login);

        Kick(playerid);
    }
}

stock Account_OnPlayerDisconnect(playerid) {
    if(IsPlayerLogged(playerid)) {
        static const
            fmt_query[] = "\
            UPDATE \
                "#MYSQL_TABLE_USERS" \
            SET \
                Online = '0', \
                LastdateUnix = CURRENT_TIMESTAMP, \
                Lastip = INET_ATON('%e') \
            WHERE \
                ID = '%i' \
            LIMIT 1";
        new query[sizeof(fmt_query) + (-2 + MAX_IP_LENGHT) + (-2 + 11)];
        mysql_format(
            dbHandle, query, sizeof(query),
            fmt_query,
            account_info[playerid][account_IP],
            account_info[playerid][account_ID]
        );
        mysql_tquery(dbHandle, query);

        Player_OnPlayerDisconnect(playerid);

        PlayerInformationClear(playerid);
    }
}

public: OnPlayerLoadingAccount(playerid) {
    new rows;
    cache_get_row_count(rows);

    if(!rows) {
        printf(">> !! ОШИБКА ЗАГРУЗКИ АККАУНТА: АККАУНТ %s НЕ НАЙДЕН! [MYSQL_ERROR_LOADING_ACCOUNT]", account_info[playerid][account_Login]);
        SendErrorMessage(playerid, "Произошла ошибка [MYSQL_ERROR_LOADING_ACCOUNT]. Напишите проблему в технический раздел на форуме, приложив данную ошибку");
        Kick(playerid);
        return 1;
    }

    cache_get_value_name_int(0, !"Regdate", account_info[playerid][account_RegDateUnix]);
    cache_get_value_name(0, !"RegIPVarchar", account_info[playerid][account_RegIP], MAX_IP_LENGHT);
    cache_get_value_name_int(0, !"Lastdate", account_info[playerid][account_LastDateUnix]);
    cache_get_value_name(0, !"LastIPVarchar", account_info[playerid][account_LastIP], MAX_IP_LENGHT);
    cache_get_value_name(0, !"InviteCode", account_info[playerid][account_InviteCode], MAX_INVITE_CODE_LENGHT);

    new 
        temp_date[25],
        str[38 + 25]
    ;
    cache_get_value_name(0, !"LastdateUnix", temp_date, sizeof(temp_date));
    format(
        str, sizeof(str),
        "Последний раз вы заходили на сервер: %s",
        temp_date
    );
    SendClientMessage(playerid, COLOR_LGR, str);

    static const
        fmt_query[] = "\
        UPDATE \
            "#MYSQL_TABLE_USERS" \
        SET \
            LastdateUnix = CURRENT_TIMESTAMP, \
            Lastip = INET_ATON('%e') \
        WHERE \
            ID = '%i' \
        LIMIT 1"
    ;
    new query[sizeof(fmt_query) + (-2 + MAX_IP_LENGHT) + (-2 + 11)];
    mysql_format(
        dbHandle, query, sizeof(query),
        fmt_query,
        account_info[playerid][account_IP],
        account_info[playerid][account_ID]
    );
    mysql_tquery(dbHandle, query);

    TogglePlayerBackground(playerid, 1000, CHARACTER_SELECT_BACKGROUND_ID);
    return 1;
}