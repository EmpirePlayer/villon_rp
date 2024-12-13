stock OnPlayerRegister(playerid) {
    SetPVarInt(playerid, pVar__Timer_Login, gettime() + (UNIX_MINUTE * MAX_MINUTE_REGISTRATION));

    PlayerPlaySound(playerid, 1187, 0.0, 0.0, 0.0);

    new str[66 + MAX_PLAYER_NAME];
    format(
        str, sizeof(str),
        "Добро пожаловать, %s. Надеемся, что вы хорошо проведете время у нас!",
        account_info[playerid][account_Login]
    );
    SendClientMessage(playerid, 0xF5DEB3FF, str);

    Dialog_Create(playerid, Dialog:Registration);
}

dialog Registration(playerid) {
    Create:<""#C_B"Регистрация | "#C_W"Ввод пароля"> {
        ResponseRight: {
            PlayerClearChat(playerid);
            Kick(playerid);

            SendClientMessage(playerid, 0xF5DEB3FF, !"До встречи, мы надеемся увидеть вас вновь на нашем сервере");
            return DIALOG_CLOSE;
        }

        Input:<"\
            "#C_W"Прежде чем начать игру, Вы должны пройти\n\
            регистрацию. Она включает в себя\n\
            следующие этапы\n\n\
            \t"#C_LIGHTGRAY"1. Пароль\n\
            \t"#C_DIMGRAY"2. Инвайт-код\n\n\
            "#C_W"Придумайте и введите уникальный пароль\n\
            не используемый на остальных проектах\
        "> {
            new password[MAX_PASSWORD_LENGHT + 1];
            Dialog_Text(playerid, password);

            if(!textlen(password, MIN_PASSWORD_LENGHT, MAX_PASSWORD_LENGHT)) {
                PlayerClearChat(playerid);
                SendErrorMessage(playerid, "Длина пароля должна быть от "#MIN_PASSWORD_LENGHT" до "#MAX_PASSWORD_LENGHT" символов");
                return DIALOG_REOPEN;
            }

            new Regex:PASSWORD_CHECK_VALID = Regex_New("^[a-zA-Z0-9]{1,}$");
		    if(Regex_Check(password, PASSWORD_CHECK_VALID)) {
                for(new i; i < 10; i++) {
                    account_info[playerid][account_Salt][i] = random(79) + 47;
                }
                account_info[playerid][account_Salt][10] = 0;
                SHA256_PassHash(password, account_info[playerid][account_Salt], account_info[playerid][account_Password], MAX_SALT_PASSWORD_LENGHT);

                Create:<""#C_B"Регистрация | "#C_W"Инвайт-код"> {
                    ResponseRight: {
                        return DIALOG_BACK;
                    }

                    Input:<"\
                        "#C_W"Прежде чем начать игру, Вы должны пройти\n\
                        регистрацию. Она включает в себя\n\
                        следующие этапы\n\n\
                        \t"#C_DIMGRAY"1. Пароль\n\
                        \t"#C_LIGHTGRAY"2. Инвайт-код\n\n\
                        "#C_W"Введите инвайт-код друга вы получите \n\
                        на 3 уровне деньги. Если его нет, можете\n\
                        оставить поле пустым\
                    "> {
                        new invite_code[MAX_INVITE_CODE_LENGHT + 1];
                        Dialog_Text(playerid, invite_code);

                        if(!isnull(invite_code)) { 
                            static const
                                fmt_query_find_invite_code[] = "\
                                    SELECT \
                                        userID \
                                    FROM \
                                        "#MYSQL_TABLE_INVITE_CODE" \
                                    WHERE \
                                        code = '%e' \
                                    LIMIT 1";

                            new 
                                query[sizeof(fmt_query_find_invite_code) + (-2 + MAX_INVITE_CODE_LENGHT)],
                                deepid = Dialog_GetDeep(playerid)
                            ;

                            mysql_format(
                                dbHandle, query, sizeof(query), 
                                fmt_query_find_invite_code, 
                                invite_code
                            );
                            DialogQuery:<dbHandle, query>;

                            if(!cache_num_rows()) {
                                PlayerClearChat(playerid);
                                SendErrorMessage(playerid, "Данный инвайт-код не найден");
                                Dialog_CacheDestroy(playerid, deepid);
                                return DialogGoto:<deepid>;
                            }

                            strmid(account_info[playerid][account_InviteCode], invite_code, 0, MAX_INVITE_CODE_LENGHT, MAX_INVITE_CODE_LENGHT);
                        }

                        Create:<""#C_B"Регистрация | "#C_W"Завершение"> {
                            static const 
                                fmt_str[] = ""#C_W"Регистрация завершена. Ниже представлены указанные данные:\n\n\
                                \t"#C_LIGHTGRAY"Логин: "#C_W"%s\n\
                                \t"#C_LIGHTGRAY"Пароль: "#C_W"%s\n\
                                \t"C_LIGHTGRAY"Инвайт-Код: "#C_W"%s\n\n\
                                Сделайте {DABA3A}скришнот "#C_W" при помощи {DABA3A}F8 "#C_W"и перейдите к следующему меню";

                            new str[sizeof(fmt_str) + (-2 + MAX_PLAYER_NAME + 1) + (-2 + MAX_PASSWORD_LENGHT + 1) + (-2 + MAX_INVITE_CODE_LENGHT + 1)];
                            format(
                                str, sizeof(str), 
                                fmt_str, 
                                account_info[playerid][account_Login], 
                                password, 
                                (isnull(invite_code)) ? ("Не указан") : (invite_code)
                            );

                            MessageBox:<str> {
                                PlayerGotoSkinSelect(playerid);
                            }
                            Button:<"Завершить">;
                        }
                    }
                    Button:<"Далее", "Назад">;
                }
            } else {
                PlayerClearChat(playerid);
                Regex_Delete(PASSWORD_CHECK_VALID);

                SendErrorMessage(playerid, "Пароль может состоять только из Английских букв и цифр");
                return DIALOG_REOPEN;
            }
            Regex_Delete(PASSWORD_CHECK_VALID);
        }
    }
    Button:<"Далее", "X">;
}

stock CreateNewAccount(playerid) {
    player_info[playerid][p_Money] = START_PLAYER_MONEY;
    player_info[playerid][p_Lvl] = START_PLAYER_LEVEL;

    GetPlayerIp(playerid, account_info[playerid][account_RegIP], MAX_IP_LENGHT + 1);
    GetPlayerIp(playerid, account_info[playerid][account_LastIP], MAX_IP_LENGHT + 1);

    account_info[playerid][account_RegDateUnix] = gettime();
    account_info[playerid][account_LastDateUnix] = gettime();

    static const
        fmt_query_users[] = "\
            INSERT INTO \
                "#MYSQL_TABLE_USERS" \
                (Login, Password, Salt, Regip, Lastip, InviteCode, Online) \
            VALUES \
                ('%q', '%q', '%q', INET_ATON('%q'), INET_ATON('%q'), '%q', '1')\
        ",
        fmt_query[] = "\
            SELECT \
                ID \
            FROM \
                "#MYSQL_TABLE_USERS" \
            WHERE \
                Login = '%e' \
            LIMIT 1"
    ;

    new 
        query_users[sizeof(fmt_query_users) + (-2 + MAX_PLAYER_NAME) + (-2 + MAX_SALT_PASSWORD_LENGHT) + (-2 + MAX_SALT_LENGHT) + (-2 + MAX_IP_LENGHT) * 2 + (-2 + MAX_INVITE_CODE_LENGHT)],
        query[sizeof(fmt_query) + (-2 + MAX_PLAYER_NAME)]
    ;
    format(
        query_users, sizeof(query_users),
        fmt_query_users,
        account_info[playerid][account_Login],
        account_info[playerid][account_Password],
        account_info[playerid][account_Salt],
        account_info[playerid][account_RegIP],
        account_info[playerid][account_LastIP],
        account_info[playerid][account_InviteCode]
    );
    mysql_tquery(dbHandle, query_users);

    mysql_format(
        dbHandle, query, sizeof(query),
        fmt_query,
        account_info[playerid][account_Login]
    );
    mysql_tquery(
        dbHandle, 
        query, 
        !"LoadingPlayerRegistration", 
        !"i", 
        playerid
    );
}

public: LoadingPlayerRegistration(playerid) {
    new rows;
    cache_get_row_count(rows);

    if(!rows) {
        printf(">> !! ОШИБКА РЕГИСТРАЦИИ АККАУНТА: АККАУНТ %s НЕ НАЙДЕН! [MYSQL_ERROR_REGISTRATION_PLAYER]", account_info[playerid][account_Login]);
        SendErrorMessage(playerid, "Произошла ошибка [MYSQL_ERROR_REGISTRATION_PLAYER]. Напишите проблему в технический раздел на форуме, приложив данную ошибку");
        Kick(playerid);
        return 1;
    }

    cache_get_value_name_int(0, "ID", account_info[playerid][account_ID]);

    #if DEBUG_MODE
        printf("ACCOUNT_REGISTER %d: >> Зарегистрирован новый логин %s [regip: %s, lastip: %s, invite_code: %s], Персонаж %s [skin: %d, money: %d]",
            account_info[playerid][account_ID],
            account_info[playerid][account_Login],
            account_info[playerid][account_RegIP],
            account_info[playerid][account_LastIP],
            account_info[playerid][account_InviteCode],
            player_info[playerid][p_Name],
            player_info[playerid][p_Skin],
            player_info[playerid][p_Money]
        );
    #endif

    static const
        fmt_query_character[] = "\
            INSERT INTO \
                "#MYSQL_TABLE_CHARACTER" \
                (userID, Name, National, Sex, Money, Lvl, Exp, Age, StyleChat, Skin) \
            VALUES \
                ('%i', '%q', '%i', '%i', '%i', '%i', '%i', '%i', '%i', '%i')\
        ";
    
    new query[sizeof(fmt_query_character) + (-2 + MAX_PLAYER_NAME) + (-2 + 11) * 6 + (8)];
    format(
        query, sizeof(query),
        fmt_query_character,
        account_info[playerid][account_ID],
        player_info[playerid][p_Name],
        player_info[playerid][p_National],
        player_info[playerid][p_Sex],
        player_info[playerid][p_Money],
        player_info[playerid][p_Lvl],
        player_info[playerid][p_Exp],
        player_info[playerid][p_Age],
        player_info[playerid][p_StyleChat],
        player_info[playerid][p_Skin]
    );
    mysql_tquery(dbHandle, query);

    TogglePlayerBackground(playerid, 1000, CHARACTER_SELECT_BACKGROUND_ID);
    return 1;
}

stock AccountReg_BackgroundUpdate(playerid, status) {
    if(status == BACKGROUND_STATUS_ON) {
        TogglePlayerControllable(playerid, false);
        SetPlayerPos(playerid, 1128.6995,-1491.3666,22.7690);
        SetPlayerCameraPos(playerid, 1129.2462,-1488.1359,23.9830);
        SetPlayerCameraLookAt(playerid, 1128.8005,-1492.2363,22.7690);
        SetPlayerFacingAngle(playerid, 355.0);
    } else {
        static const
            fmt_query_loading[] = "\
            SELECT \
                ID, \
                UCASE(`Name`) AS NameUP, \
                Skin \
            FROM \
                "#MYSQL_TABLE_CHARACTER" \
            WHERE \
                userID = '%i'"
        ;
        new query_loading[sizeof(fmt_query_loading) + (-2 + 11)];
        mysql_format(
            dbHandle, query_loading, sizeof(query_loading),
            fmt_query_loading,
            account_info[playerid][account_ID]
        );
        mysql_tquery(
            dbHandle,
            query_loading,
            !"OnPlayerSelectCharacter",
            !"d",
            playerid
        );

        if(!isnull(player_info[playerid][p_Name])) {
            new str[50 + MAX_PLAYER_NAME];
            format(
                str, sizeof(str),
                "Ваш персонаж "#C_GREEN"%s "#C_W"успешно создан",
                player_info[playerid][p_Name]
            );
            SendClientMessage(playerid, COLOR_WHITE, str);
        }
        SendClientMessage(playerid, COLOR_WHITE, !"Чтобы начать игру нажмите "#C_G"НАЧАТЬ ИГРУ");
    }
}