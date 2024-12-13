new gServerTimer;

stock Server_Time_GameModeInit() {
    SetTimer(!"OnServerSecondUpdate", 1000, true);
}

public: OnServerSecondUpdate() {
    if(++gServerTimer == 60) { // 1 минута
        gServerTimer = 0;
    }

    foreach(new i: Player) {
        if(!IsPlayerLogged(i)) {
            PlayerTimerAccountLogin(i);
        }
    }
}