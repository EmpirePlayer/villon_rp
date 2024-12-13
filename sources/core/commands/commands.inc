#include "player_commands"

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags) {
    if(!IsPlayerLogged(playerid)) {
        return 0;
    }

    if(result == -1) {
        PlayerInvalidCommand(playerid);
        return 0;
    } else {
        temp_info[playerid][tCommandSucces] = true;
    }
    return 1;
}

public OnPlayerCommandReceived(playerid, cmd[], params[], flags) {
    if(!IsPlayerLogged(playerid)) {
        return 0;
    }

    if(temp_info[playerid][tCommandSucces]) {
        if(PlayerAntiFlood(playerid)) {
            SendClientMessage(playerid, COLOR_GREY, !"Подождите немного...");
            return 0;
        }
    }

    if(Dialog_IsRender(playerid)) {
        SendClientMessage(playerid, COLOR_GREY, !"Нельзя использовать команды, пока открыт диалог");
        return 0;
    }
    return 1;
}