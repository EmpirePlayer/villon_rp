// Перехват OnGameModeInit
public OnGameModeInit() {
    MySQL_Connect_OnGameModeInit(); // Перехват в sources/core/mysql_connect.inc

    TextDraw_OnGameModeInit();

    mysql_tquery(dbHandle, !"UPDATE "#MYSQL_TABLE_USERS" SET Online = '0'");

    Iter_Clear(ITER_pLogged);

    Server_Time_GameModeInit();

    SendRconCommand(SERVER_HOST_NAME); 					
    SendRconCommand(SERVER_MODE);		 						
    SendRconCommand(SERVER_LANGUAGE); 							
    SendRconCommand("weburl "#SERVER_SITE""); 				
	return 1;
}

public OnGameModeExit() {
    Iter_Clear(ITER_pLogged);

    KillAllTimers();
    mysql_close(dbHandle);
    print(">> Gamemode ended");
    return 1;
}

public OnPlayerRequestClass(playerid, classid) {
    Account_RequestClass(playerid);
    return 1;
}

public OnPlayerSpawn(playerid) {
    Account_Spawn(playerid);
    return 1;
}

public OnPlayerConnect(playerid) {
    Player_OnPlayerConnect(playerid);
    return 1;
}

public OnPlayerDisconnect(playerid, reason) {
    Account_OnPlayerDisconnect(playerid);
    BCKGRND_OnPlayerDisconnect(playerid);
    return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid) {
    ChCreate_PlayerClickTextDraw(playerid, clickedid);
    Character_PlayerClickTextDraw(playerid, clickedid);
    return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {
    ChCreate_PlayerClickPTextDraw(playerid, playertextid);
	return 1;
}

public OnPlayerText(playerid, text[]) {
    chat_OnPlayerText(playerid, text);
    return 0;
}

public OnPlayerBackgroundUpdate(playerid, backgroundid, status) {
    switch(backgroundid) {
        case CHARACTER_SELECT_BACKGROUND_ID: {
            AccountReg_BackgroundUpdate(playerid, status);
        }
        case CHARACTER_LOAD_BACKGROUND_ID: {
            CharacterLoad_BackgroudUpdate(playerid, status);
        }
    }
    return 1;
}