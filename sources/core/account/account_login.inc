stock OnPlayerLogin(playerid) {
    SetPVarInt(playerid, pVar__Timer_Login, gettime() + (UNIX_MINUTE * MAX_MINUTE_LOGIN));

    cache_get_value_name_int(0, "ID", account_info[playerid][account_ID]);
    cache_get_value_name(0, !"Password", account_info[playerid][account_Password], MAX_SALT_PASSWORD_LENGHT);
    cache_get_value_name(0, !"Salt", account_info[playerid][account_Salt], MAX_SALT_LENGHT);
    Dialog_Create(playerid, Dialog:Login);
}

dialog Login(playerid) {
    Create: <""#C_B"����������� | "#C_W"���� ������"> {
        ResponseRight: {
            PlayerClearChat(playerid);
            Kick(playerid);

            SendClientMessage(playerid, 0xF5DEB3FF, !"�� �������, �� �������� ������� ��� ����� �� ����� �������");
            return DIALOG_CLOSE;
        }

        Input:<"\
            "#C_W"������������ ��� �� ����� �������!\n\n\
            ����� � ����� ��������� ��� ���������������\n\
            ������� ������ �� �������� � ���� ����::\
        "> {
            new password[MAX_PASSWORD_LENGHT + 1];
            Dialog_Text(playerid, password);

            if(!textlen(password, MIN_PASSWORD_LENGHT, MAX_PASSWORD_LENGHT)) {
                PlayerClearChat(playerid);

                SendErrorMessage(playerid, "������������ {33aa33}20{afafaf}, ����������� {33aa33}6{afafaf} �������� ����� ������");
                return DIALOG_REOPEN;
            }

            new hash[65];
		    SHA256_PassHash(password, account_info[playerid][account_Salt], hash, MAX_SALT_PASSWORD_LENGHT);
            if(!GetString(hash, account_info[playerid][account_Password])) {
                PlayerClearChat(playerid);

                if(!--temp_info[playerid][tLoginAttemps]) {
                    PlayerClearChat(playerid);
                    Kick(playerid);

                    SendClientMessage(playerid, 0xD8A903FF, !"�� ��������� ���������� ����� ������� ����� � �������. ��� ������ ����������� (/q)uit");
                    return DIALOG_CLOSE;
                }

                new str[70];
                format(
                    str, sizeof(str),
                    "�� ����� ������������ ������. �������� {FF8282}%d{afafaf} �������",
                    temp_info[playerid][tLoginAttemps]
                );
                SendClientMessage(playerid, COLOR_GREY, str);
                return DIALOG_REOPEN;
            }

            PlayerClearChat(playerid);

            static const 
                fmt_query[] = "\
                SELECT \
                    *, \
                    UNIX_TIMESTAMP(RegdateUnix) AS Regdate, \
                    UNIX_TIMESTAMP(LastdateUnix) AS Lastdate, \
                    INET_NTOA(Regip) AS RegIPVarchar, \
                    INET_NTOA(Lastip) AS LastIPVarchar \
                FROM \
                    "#MYSQL_TABLE_USERS" \
                WHERE \
                    ID = '%i' \
                LIMIT 1";
            new query[sizeof(fmt_query) + (-2 + 11)];
            mysql_format(
                dbHandle, query, sizeof(query),
                fmt_query,
                account_info[playerid][account_ID]
            );
            mysql_tquery(
                dbHandle, query, 
                !"OnPlayerLoadingAccount", 
                !"d", 
                playerid
            );
        }
    }
    Button:<"�����", "X">;
}