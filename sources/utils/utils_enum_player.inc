#define     MAX_SALT_PASSWORD_LENGHT    65
#define     MAX_SALT_LENGHT             11
#define     MAX_IP_LENGHT               16

#define 	MIN_PASSWORD_LENGHT			6
#define 	MAX_PASSWORD_LENGHT			20

#define     MAX_INVITE_CODE_LENGHT      20
#define     MAX_STYLE_CHAT_COUNT        2

#define     MIN_PLAYER_AGE              18
#define     MAX_PLAYER_AGE              50

enum {
    PLAYER_SEX_FEMALE,
    PLAYER_SEX_MALE
}

enum {
    PLAYER_NATIONAL_EUROPEAN,
    PLAYER_NATIONAL_AFRO_AMERICAL,
    PLAYER_NATIONAL_LATINOS,
    PLAYER_NATIONAL_ASIAN
}

enum E_ACCOUNT_INFORMATION {
    account_ID,
    account_Login[MAX_PLAYER_NAME + 1],

    account_IP[MAX_IP_LENGHT + 1],
    account_RegDateUnix,
    account_RegIP[MAX_IP_LENGHT + 1],
    account_LastDateUnix,
    account_LastIP[MAX_IP_LENGHT + 1],

    account_Password[MAX_SALT_PASSWORD_LENGHT + 1],
    account_Salt[MAX_SALT_LENGHT + 1],

    account_InviteCode[MAX_INVITE_CODE_LENGHT + 1],
}
new account_info[MAX_PLAYERS][E_ACCOUNT_INFORMATION];

new defaultAccountInfo[E_ACCOUNT_INFORMATION] = {
    -1,
    EOS,

    EOS,
    -1,
    EOS,
    -1,
    EOS,

    EOS,
    EOS,

    EOS,
};

enum E_PLAYER_INFORMATION {
    p_ID,
    p_Name[MAX_PLAYER_NAME + 1],

    p_National,
    p_Sex,
    p_Skin,
    p_Age,
    p_StyleChat,

    p_Money,
    p_Lvl,
    p_Exp,

    p_RegDateUnix,
    p_LastDateUnix,
}
new player_info[MAX_PLAYERS][E_PLAYER_INFORMATION];

new defaultPlayerInfo[E_PLAYER_INFORMATION] = {
    -1,
    EOS,

    0,
    1,
    45,
    MIN_PLAYER_AGE,
    0,

    0,
    0,
    0,

    -1,
    -1,
};

enum E_TEMP_PLAYER_INFORMATION {
    bool:tRequest,
    tLoginAttemps, 
    bool:tCommandSucces, 
}
new temp_info[MAX_PLAYERS][E_TEMP_PLAYER_INFORMATION];

new defaultTempInfo[E_TEMP_PLAYER_INFORMATION] = {
    true,
    3,
    false,
};