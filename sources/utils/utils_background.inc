/* 

    M I S T E V

*/

// ALS prefix BCKGRND


#if !defined _samp_included

    #error Please include <a_samp> first

#endif


#if defined _background_included

    #endinput

#endif

#define _background_included


#if !defined BACKGROUND_TIMER_INTERVAL

    #define BACKGROUND_TIMER_INTERVAL 20 // ms

#endif


#if !defined BACKGROUND_SIZE_WIDTH

    #define BACKGROUND_SIZE_WIDTH 640.0

#endif


#if !defined BACKGROUND_SIZE_HEIGHT

    #define BACKGROUND_SIZE_HEIGHT 480.0

#endif


#if !defined BACKGROUND_COLORS

    static const BACKGROUND_COLORS[] = 
    {
        0x00000000,
        0x00000011,
        0x00000022,
        0x00000033,
        0x00000044,
        0x00000055,
        0x00000066,
        0x00000077,
        0x00000088,
        0x00000099,
        0x000000AA,
        0x000000BB,
        0x000000CC,
        0x000000DD,
        0x000000EE,
        0x000000FF,
    };

#endif


forward OnPlayerBackgroundUpdate(playerid, backgroundid, status);

forward ShowBackground(playerid);
forward HideBackground(playerid);


enum BACKGROUND_INFORMATION
{
    PlayerText:bgTD,

    bgID,
    bgColor,
    bgPause,
    bgTimer
}
new bgInfo[MAX_PLAYERS][BACKGROUND_INFORMATION];


#if defined BACKGROUND_STATUS_OFF

    #error symbol already defined: "BACKGROUND_STATUS_OFF"

#else

    #define BACKGROUND_STATUS_OFF 0

#endif


#if defined BACKGROUND_STATUS_ON

    #error symbol already defined: "BACKGROUND_STATUS_ON"

#else

    #define BACKGROUND_STATUS_ON 1

#endif


stock CreateBackgroundTextDraw(playerid)
{
    bgInfo[playerid][bgTD] = 
    CreatePlayerTextDraw        (playerid, 0.0, 0.0, !"_");
    PlayerTextDrawLetterSize    (playerid, bgInfo[playerid][bgTD], BACKGROUND_SIZE_WIDTH, BACKGROUND_SIZE_HEIGHT);
    PlayerTextDrawUseBox        (playerid, bgInfo[playerid][bgTD], 1);
    PlayerTextDrawBoxColor      (playerid, bgInfo[playerid][bgTD], 0x00000000);
    PlayerTextDrawShow          (playerid, bgInfo[playerid][bgTD]);
}


stock DestroyBackgroundTextDraw(playerid)
{
    return PlayerTextDrawDestroy(playerid, bgInfo[playerid][bgTD]);
}


stock TogglePlayerBackground(playerid, pause=0, backgroundid=1)
{
    if(bgInfo[playerid][bgID])
        return 0;

    CreateBackgroundTextDraw(playerid);

    bgInfo[playerid][bgID] = backgroundid;
    bgInfo[playerid][bgColor] = 0;
    bgInfo[playerid][bgPause] = pause;

    return bgInfo[playerid][bgTimer] = SetTimerEx(
        !"ShowBackground", 
        BACKGROUND_TIMER_INTERVAL, 
        false, 
        !"i", 
        playerid
    );
}


public ShowBackground(playerid)
{
    if(bgInfo[playerid][bgColor] < sizeof BACKGROUND_COLORS - 1)
    {
        bgInfo[playerid][bgColor]++;

        PlayerTextDrawBoxColor(playerid, bgInfo[playerid][bgTD], BACKGROUND_COLORS[bgInfo[playerid][bgColor]]);
        PlayerTextDrawShow(playerid, bgInfo[playerid][bgTD]);

        bgInfo[playerid][bgTimer] = SetTimerEx(
            !"ShowBackground", 
            BACKGROUND_TIMER_INTERVAL, 
            false, 
            !"i", 
            playerid
        );
    }
    else
    {
        bgInfo[playerid][bgTimer] = SetTimerEx(
            !"HideBackground", 
            bgInfo[playerid][bgPause], 
            false, 
            !"i", 
            playerid
        );

        OnPlayerBackgroundUpdate(playerid, bgInfo[playerid][bgID], BACKGROUND_STATUS_ON);
    }

    return 1;
}


public HideBackground(playerid)
{
    if(bgInfo[playerid][bgColor] > 0)
    {
        bgInfo[playerid][bgColor]--;

        PlayerTextDrawBoxColor(playerid, bgInfo[playerid][bgTD], BACKGROUND_COLORS[bgInfo[playerid][bgColor]]);
        PlayerTextDrawShow(playerid, bgInfo[playerid][bgTD]);

        bgInfo[playerid][bgTimer] = SetTimerEx(
            !"HideBackground", 
            BACKGROUND_TIMER_INTERVAL, 
            false, 
            !"i", 
            playerid
        );
    }
    else
    {
        OnPlayerBackgroundUpdate(playerid, bgInfo[playerid][bgID], BACKGROUND_STATUS_OFF);

        DestroyBackgroundTextDraw(playerid);

        bgInfo[playerid][bgID] = 0;
        bgInfo[playerid][bgColor] = 0x00000000;
        bgInfo[playerid][bgPause] = 0;

        KillTimer(bgInfo[playerid][bgTimer]);
    }

    return 1;
}


stock BCKGRND_OnPlayerDisconnect(playerid)
{
    DestroyBackgroundTextDraw(playerid);

    bgInfo[playerid][bgID] = 0;
    bgInfo[playerid][bgColor] = 0x00000000;
    bgInfo[playerid][bgPause] = 0;

    KillTimer(bgInfo[playerid][bgTimer]);

    return 1;
}