/*

[ == RTCW CLIENTHOOK == ]
made by vasyan, 2020
credits: RTCW Source Code, IDA Pro :-)

Since the game uses idTech 3, it was fairly easy to "dive in",
because I've worked with idTech 2 and Call of Duty games a bit.
There's more difference between idTech 3 and 4, than idTech 3 and
latest CoD game.

THIS CODE IS WRITTEN FOR VERSION 1.32 OF RTCW! (which is distributed via Steam)
If you want to use this cheat for any other version (like iortcw), you'll have to
get proper function offsets for that version.
Other than that, I suppose this cheat will work without any other modifications.

Also, I guess it's worth mentioning this cheat is for singleplayer only,
if you didn't figure it out yet.

*/
#include "framework.h"
#include "funcs.h"
#include "hooks.h"
#include "menu.h"

void InitFunc()
{
	engine::com_printf("RtcW ClientHook :: Injected\n");
	engine::cbuf_addtext("unbind LEFTARROW; unbind RIGHTARROW; unbind UPARROW; unbind DOWNARROW;");
    engine::cvar_set("seta r_znear", "1", qtrue); //sky cuts off at high fov values, fix that
	menu::add_items();
	hooks::init();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		InitFunc();
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

