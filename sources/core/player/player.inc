#include "player_CharacterCreate"
#include "player_CharacterSelect"
#include "player_CharacterLoading"

stock PlayerSettingsSpawn(playerid) {
    SetPlayerPos(playerid, 1760.4858, -1895.8802, 13.5615);
	SetPlayerFacingAngle(playerid, 268.0);

    SetCameraBehindPlayer(playerid);

	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	SetPlayerSkin(playerid, player_info[playerid][p_Skin]);
	SetPlayerColor(playerid, 0xFFFFFF50);
}

stock Player_OnPlayerConnect(playerid) {
    SetPlayerColor(playerid, COLOR_GREY); 							/* Устанавливаем серый клист для игрока */

	ResetPlayerWeapons(playerid); 									/* Удаляем оружие */
	SetPlayerArmedWeapon(playerid, 0); 								/* Делаем кулак основным */
	StopAudioStreamForPlayer(playerid); 							/* Остановим аудио в скриме */
	CancelSelectTextDraw(playerid); 								/* Убираем режим выбора TextDraw */

    PlayerInformationClear(playerid);

    GetPlayerIp(playerid, account_info[playerid][account_IP], MAX_IP_LENGHT);
    GetPlayerName(playerid, account_info[playerid][account_Login], MAX_PLAYER_NAME);	    /* Узнаем Ник у игрока и запишем для Логина */

	PreloadAnimLibs(playerid);
}

stock Player_OnPlayerDisconnect(playerid) {
    Iter_Remove(ITER_pLogged, playerid); 
}

stock PlayerInformationClear(playerid) {
    account_info[playerid] = defaultAccountInfo;
    player_info[playerid] = defaultPlayerInfo;
    temp_info[playerid] = defaultTempInfo;

	for(new i; i < MAX_PLAYER_CHARACTER_AMOUNT; i++) {
        pLoadingsID[playerid][i] = -1;
    }
}

stock SetPlayerLogged(playerid, const bool: value) {
    pLogged{playerid} = value;
}

stock IsPlayerLogged(playerid) {
    return pLogged{playerid};
}

stock PlayerClearChat(playerid) {
	static const
		str[] = !#;

	new i_1 = 100;
	#emit 	push.c 		 str
	#emit 	push.c 		 0
	#emit 	push.S 		 playerid
	#emit 	push.c 		 12

	do {
		#emit 	sysreq.c 	SendClientMessage
	}
	while(--i_1);

	#emit 	stack 		 16
}