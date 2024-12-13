#include    "utils_colour"
#include    "utils_enum_player"
#include	"utils_preloadanims"
#include	"utils_background"
#include	"utils_ProxDetector"

new _macros_new_num;
#define PluralToText(%0,%1,%2,%3) \ 
                    ((_macros_new_num = ((%0 % 100) >= 20 ? (%0 % 10) : %0)) == 1 ? (%1) : (2 <= _macros_new_num <= 4 ? (%2) : (%3)))

#define PLAYER_ANTI_FLOOD_TIME	3

stock PlayerAntiFlood(playerid) {
	static anti_flood[MAX_PLAYERS];

	if(anti_flood[playerid] > gettime())
		return 1;

	anti_flood[playerid] = gettime() + PLAYER_ANTI_FLOOD_TIME;
	return 0;
}

stock string_replace(inputvar[], const searchstring[], const replacestring[], bool: ignorecase = true, bool: replaceall = false) {
	if(strfind(replacestring, searchstring, ignorecase) != -1)
		return -1;

	new pos = strfind(inputvar, searchstring, ignorecase);

	if(pos == -1)
		return 0;

	if(replaceall == true) {
		while(strfind(inputvar, searchstring, ignorecase) != -1) {
			pos = strfind(inputvar, searchstring, ignorecase);
			strdel(inputvar, pos, pos+strlen(searchstring));
			strins(inputvar, replacestring, pos, strlen(inputvar));
		}
	}
	else {
		strdel(inputvar, pos, pos+strlen(searchstring));
		strins(inputvar, replacestring, pos, strlen(inputvar));
	}
	return 1;
}

stock Float:frandom(Float:max) { 
	return floatdiv(float(random(0)), floatdiv(float(cellmax), max)); 
}

stock Float:mathfrandom(Float:min, Float:max) { 
	return floatadd(frandom(floatsub(max, min)), min); 
}

stock GivePlayerMoneyEx(const playerid, const money, const text[] = "") {
	if(!isnull(text)) {
		PlayerLogAdd(playerid, TYPE_LOG_MONEY, text);
	}
	GivePlayerMoney(playerid, money);
}

stock SetString(param_1[], param_2[], size = 300) {
	return strmid(param_1, param_2, 0, strlen(param_2), size);
}

stock GetString(param1[], param2[]) {
	return !strcmp(param1, param2, false);
}

stock ex_SendClientMessage(playerid, color, const message[], color1 = -2) {
	new
		length = strlen(message),
		outstr[128],
		trim
	;

	if(length > 127) {
		for (new i = 127; i>=0; i--) {
			trim = i;

			if(message[i] == ' ')
				break;
		}

		if(trim < 64)
			trim = 127;

		strmid(outstr, message, 0, trim, 128);
		SendClientMessage(playerid, color, outstr);

		strmid(outstr, message, trim, length, 128);
		SendClientMessage(playerid, (color1 == -2) ? (color) : (color1), outstr);
	}
	else SendClientMessage(playerid, color, message);
  	return 1;
}

#if defined _ALS_SendClientMessage
	#undef SendClientMessage
#else
	#define _ALS_SendClientMessage
#endif

#define SendClientMessage ex_SendClientMessage

stock ex_SendClientMessageToAll(color, const message[]) {
	foreach(new i: ITER_pLogged) {
		SendClientMessage(i, color, message);
	}
}

#if defined _ALS_SendClientMessageToAll
	#undef SendClientMessageToAll
#else
	#define _ALS_SendClientMessageToAll
#endif

#define SendClientMessageToAll ex_SendClientMessageToAll