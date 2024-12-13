#undef 	MAX_PLAYERS
    #define 	MAX_PLAYERS 		            100

#undef 	MAX_VEHICLES
    #define 	MAX_VEHICLES	                1000

#define         SERVER_HOST_NAME                !"hostname |       [VILL] Villon Role Play 1     |"
#define 	    SERVER_MODE			            !"gamemodetext [ALPHA] VILL.PWN"
#define 	    SERVER_LANGUAGE		            !"language Russian"
#define 	    SERVER_VERSION		            "VILL v0.1 [ALPHA]"
#define         SERVER_NAME                     "VILL RP | 1"
#define         SERVER_SITE                     "www.vill-rp.ru"

#define   	    public:%0(%1) 	                forward%0(%1); public%0(%1)
#define   	    textlen(%0,%1,%2)	            (%1 <= strlen(%0) <= %2)

#define 	    HOLDING(%0)                     ((newkeys & (%0)) == (%0))
#define 	    PRESSED(%0)                     (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define 	    RELEASED(%0)                    (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

#define 	    SendErrorMessage(%0,%1)			SendClientMessage(%0, COLOR_GREY, !""%1)
#define 	    SendInfoMessage(%0,%1)			SendClientMessage(%0, COLOR_WEAT, !"[Информация]"C_W" "%1)
#define 	    SendSuccesMessage(%0,%1)		SendClientMessage(%0, COLOR_LGR, !"[Успешно]"C_W" "%1)
#define 	    SendServerMessage(%0,%1)		SendClientMessage(%0, COLOR_SERVER, !"[Сервер]"C_W" "%1)

#define 	    PlayerInvalidCommand(%0)		SendClientMessage(%0, COLOR_WHITE, !"SERVER: Unknown command.")

#define         DEBUG_MODE                      1

#define         START_PLAYER_MONEY              100
#define         START_PLAYER_LEVEL              1

#define         INVALID_PLAYER_TIMER_ID         -1

#define         UNIX_MINUTE 				    60 // seconds
#define         UNIX_HOUR 					    3600 // seconds
#define         UNIX_DAY					    86400 // seconds
#define         UNIX_MONTH 					    2592000 // seconds
#define         UNIX_YEAR 					    31104000 // seconds