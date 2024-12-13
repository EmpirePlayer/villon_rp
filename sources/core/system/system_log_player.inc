#define MAX_LOG_TYPE_LENGHT     14
#define MAX_LOG_MESSAGE_LENGHT  144
#define MAX_LOG_ON_PAGE         15

//new pVar__LogPageID[] = !"pVar__LogPageID";

stock PlayerLogAdd(const playerid, const E_LOG_TYPE: type, const text[], const value_user_id = -1, const value_user_ip[] = "0", const value_character_id = -1) {
    new tick_count = GetTickCount();
    
    static const
        fmt_query[] = "\
            INSERT INTO "#MYSQL_TABLE_PLAYER_LOGS" \
                (type, userID, userIP, characterID, log, content_UserID, content_UserIP, content_CharacterID) \
            VALUES \
                ('%i', '%i', INET_ATON('%e'), '%i', '%e', '%i', INET_ATON('%e'), '%i') \
        ";
    new query[sizeof(fmt_query) + ((-2 + MAX_PLAYER_NAME) * 2 + (-2 + 11) * 3 + (-2 + MAX_LOG_MESSAGE_LENGHT) + (-2 + MAX_IP_LENGHT) * 2) + 1];
    mysql_format(
        dbHandle, query, sizeof(query),
        fmt_query,
        _:type,
        account_info[playerid][account_ID],
        account_info[playerid][account_IP],
        player_info[playerid][p_ID],
        text,
        value_user_id,
        value_user_ip,
        value_character_id
    );
    mysql_tquery(dbHandle, query);

    printf(
        ">> [%d ms] Добавлен LOG %d: %s от LOGIN: %s[id_acc:%d], CHARACTER: %s на игрока id_acc:%d, id_character:%d", 
        GetTickCount() - tick_count, 
        _:type, 
        text, 
        account_info[playerid][account_Login], 
        account_info[playerid][account_ID], 
        player_info[playerid][p_Name],
        value_user_id,
        value_character_id
    );
}
