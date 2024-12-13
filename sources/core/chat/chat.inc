#include "chat_OnPlayerText"

public: PlayerClearAnimation(playerid) {
    if(pTimerClearAnims[playerid] != INVALID_PLAYER_TIMER_ID) {
        DeletePVar(playerid, pVar__AntiFlood_Anims);

        KillTimer(pTimerClearAnims[playerid]);

        #if DEBUG_MODE
		printf("[KillTimer 1] pTimerClearAnims[playerid] = '%d' killed",
			pTimerClearAnims[playerid]
		);
        #endif
        
        pTimerClearAnims[playerid] = INVALID_PLAYER_TIMER_ID;
    }

    ApplyAnimation(
        playerid, 
        !"CARRY", 
        !"crry_prtial", 
        4.0, 0, 0, 0, 0, 0, 1
    );
}