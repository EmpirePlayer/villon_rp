stock chat_OnPlayerText(playerid, text[]) {
    if(!IsPlayerConnected(playerid) || !IsPlayerLogged(playerid))
		return 0;

    if(text[0] == '.'){
		text[0] = '/';
		PC_EmulateCommand(playerid, text);
		return 0;
	}

    if(!textlen(text, 1, 127)) {
        SendErrorMessage(playerid, "Слишком большой текст");
        return 0;
    }

    new str[11 + (-2 + MAX_PLAYER_NAME) + (-2 + 4) + (-2 + 144) + 1];
    format(
        str, sizeof(str),
        "%s[%d]: %s",
        player_info[playerid][p_Name],
        playerid,
        text
    );
    ProxDetector(playerid, 20.0, COLOR_GREEN, str);

    SetPlayerChatBubble(playerid, text, COLOR_WHITE, 10.0, 10000);
    SetTimerEx(!"PlayerClearAnimation", 100 * strlen(text), false, !"i", playerid);

	switch(player_info[playerid][p_StyleChat]) {
		case 0:{
			ApplyAnimation(
				playerid,
				!"PED", !"IDLE_CHAT", 4.1, 0, 1, 1, 1, 1, 1
			);
		}
		case 1:{
			ApplyAnimation(
				playerid,
				!"LOWRIDER", !"prtial_gngtlkH",
				4.1, 0, 1, 1, 1, 1, 1
			);
		}
		case 2:{
			ApplyAnimation(
				playerid,
				!"GANGS", !"prtial_gngtlkB",
				4.1, 0, 1, 1, 1, 1, 1
			);
		}
	}
    return 0;
}