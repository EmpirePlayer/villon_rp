#include 			<a_samp>
#include    		<a_mysql>
#include    		<a_actor>
#include			<SKY>
#include    		<Pawn.Regex>
#include    		<Pawn.CMD>
#include 			<Pawn.RakNet>
#include    		<foreach>
#include    		<streamer>
#include    		<sscanf2>
#include    		<fix>
#include    		<rustext>
#include    		<mapfix>
#include			<LiveDialogs>
#include 			<weapon-config>
#include			<timerfix>
#include 			<time_t>

enum E_LOG_TYPE {
    TYPE_LOG_MONEY,
    TYPE_LOG_ADMIN,
}

enum {
    NULL_BACKGROUND_ID,

    CHARACTER_SELECT_BACKGROUND_ID,
    CHARACTER_LOAD_BACKGROUND_ID
}

new 
    Iterator:ITER_pLogged<MAX_PLAYERS>,
    bool:pLogged[MAX_PLAYERS char]  = {false, ...} /* Ïðîâåðêà íà àâòîðèçàöèþ */
;

#include			"..\\sources\\utils\\utils"
#include			"..\\sources\\core\\constans"
#include			"..\\sources\\core\\mysql_connect"

#include			"..\\sources\\core\\server\\server"
#include 			"..\\sources\\core\\textdraw\\textdraw"
#include			"..\\sources\\core\\account\\account"
#include			"..\\sources\\core\\player\\player"
#include			"..\\sources\\core\\system\\system"
#include			"..\\sources\\core\\chat\\chat"
#include			"..\\sources\\core\\commands\\commands"

#include			"..\\sources\\core\\interceptor"

main(){
	print(!">> "#SERVER_NAME" loaded"); 
	print(!">> "#SERVER_VERSION"");
	print(!">> "#SERVER_SITE"");
	print(!" ");

	#if DEBUG_MODE
		print(!">> DEBUG_MODE ÂÊËÞ×ÅÍ");
	#endif
}
