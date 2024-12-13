new 
    MySQL:dbHandle
;

#define 		MYSQL_HOST			    "MySQL-5.7"
#define 		MYSQL_USER			    "root"
#define 		MYSQL_PASS			    ""
#define 		MYSQL_DB 			    "server"

#define 		MYSQL_TABLE_USERS 		"`users`"
#define         MYSQL_TABLE_CHARACTER   "`userCharacter`"
#define         MYSQL_TABLE_INVITE_CODE "`inviteCode`"
#define         MYSQL_TABLE_PLAYER_LOGS "`playerLogs`"

stock MySQL_Connect_OnGameModeInit() {
    dbHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB);

    printf(
        "\nConnect | MySQL %s connected to (host: %s | user: %s | pass: %s | db: %s)",
        (dbHandle == MYSQL_INVALID_HANDLE || mysql_errno(dbHandle) != 0) ? ("not") : ("succeffuly"), 
        MYSQL_HOST, 
        MYSQL_USER, 
        MYSQL_PASS, 
        MYSQL_DB
    );

	mysql_query(dbHandle, !"SET NAMES cp1251");
	mysql_tquery(dbHandle, !"SET NAMES cp1251");
}