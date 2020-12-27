#include "framework.h"
#include "aimbot.h"
#include "hooks.h"
#include "q3types.h"
#include "funcs.h"
#include "variables.h"
#include "globals.h"
#include "detours.h"
#include "menu.h"

namespace hooks
{
	draw2d_t			original::oCG_Draw2D				= 0;
	predictstate_t		original::oCG_PredictPlayerState	= 0;
	bullet_fire_ext_t	original::oBullet_Fire_Extended		= 0;
	newcommands_t		original::oCL_CreateNewCommands		= 0;
	writepacket_t		original::oCL_WritePacket			= 0;

	finishmove_t		original::oCL_FinishMove			= 0;
	addrefent_t			original::oRE_AddRefEntityToScene	= 0;
	wndproc_t			original::oWndProc					= 0;
	bullet_fire_t		original::oBullet_Fire				= 0;
	renderscene_t		original::oRE_RenderScene			= 0;
	obituary_t			original::oCG_Obituary				= 0;
	calcbone_t			original::oR_CalcBoneLerp			= 0;
	buildbones_t		original::oR_BuildBones				= 0;
	setcolor_t			original::oR_SetColor				= 0;

	void __cdecl hRE_SetColor(const float* rgba)
	{
		//I tried to fix a bug that is present in RtCW
		//Game would crash if you're playing in widescreen and you finish particular missions
		//Problematic func is inlined so I don't give a shit
	}

	void __cdecl hCG_PredictPlayerState()
	{
		//can do silent here, before the original

		original::oCG_PredictPlayerState();
	}

	void __cdecl hCL_CreateNewCommands()
	{
		original::oCL_CreateNewCommands();

		//can do silent here after the original

		if (vars.aimbot.silentaim && aimbot::has_active_target)
		{
			usercmd_t* cmd = &global::cl_active->cmds[global::cl_active->cmdNumber & CMD_MASK];
			usercmd_t* prevCmd = &global::cl_active->cmds[(global::cl_active->cmdNumber - 1) & CMD_MASK];

			memcpy(prevCmd, cmd, sizeof usercmd_t);
			cmd->serverTime++;

			prevCmd->angles[0] = ANGLE2SHORT(aimbot::silent_angles[0]);
			prevCmd->angles[1] = ANGLE2SHORT(aimbot::silent_angles[1]);
			prevCmd->angles[2] = 0;

			//creds: Twice @ uc
			aimbot::fix_move(prevCmd);

			if (vars.aimbot.autofire)
				prevCmd->buttons |= 1;
		}
	}

	void __cdecl hCG_Obituary(entityState_t* ent)
	{
		auto target		= ent->otherEntityNum;
		auto attacker	= ent->otherEntityNum2;

		if(attacker = global::cg->snap->ps.clientNum && target != global::cg->snap->ps.clientNum)
			engine::cbuf_addtext("say ^1tapped!");

		original::oCG_Obituary(ent);
	}

	void __cdecl hCL_WritePacket()
	{
		//you can do silent here..
		//before the original
		
		original::oCL_WritePacket();
	}

	void __cdecl hCG_Draw2D()
	{
		if(global::is_opened)
			menu::paint();

		engine::cvar_set("cg_fov", std::to_string(vars.visuals.fov).c_str(), qtrue); //ghetto
		engine::cvar_set("sv_cheats", "1" , qtrue);

		if (global::cls->state == CA_ACTIVE)
		{
			if (vars.weapons.norecoil)
			{
				global::cg->kickAngles[0] = 0.f;
				global::cg->kickAngles[1] = 0.f;
				global::cg->kickAngles[2] = 0.f;

				global::cg->kickAVel[0] = 0.f;
				global::cg->kickAVel[1] = 0.f;
				global::cg->kickAVel[2] = 0.f;

				global::cg->recoilPitch = 0.f;
				global::cg->recoilPitchAngle = 0.f;
			}

			if (vars.aimbot.enabled)
				aimbot::run();

			if (vars.visuals.esp)
				cheat::esp();
		}

		original::oCG_Draw2D();	
	}

	void __cdecl hCL_FinishMove(usercmd_t* cmd)
	{
		if (vars.misc.bunnyhop) //not working
		{
			if (global::pm->ps->pm_flags & PMF_JUMP_HELD && global::pm->ps->groundEntityNum == ENTITYNUM_NONE)
			{
   				global::pm->ps->pm_flags &= ~PMF_JUMP_HELD;
			}
		}

		original::oCL_FinishMove(cmd);
	}

	void __cdecl hBullet_Fire_Extended(gentity_t *source, gentity_t *attacker, vec3_t start, vec3_t end, float spread, int damage, int recursion)
	{
		if (source->s.number == global::cg->predictedPlayerState.clientNum)
		{
			
		}

		original::oBullet_Fire_Extended(source, attacker, start, end, spread, damage, recursion);
	}

	void __cdecl hBullet_Fire(gentity_t* ent, float spread, int damage)
	{
		if (ent->s.number == 0)
		{
			if (vars.weapons.nospread)
				spread = 0.f;

			if (vars.weapons.highdamage)
				damage = 65535; //int_max causes dead enemies to become alive again if you shoot their bodies lmao

		}

		//enemies' bullets don't exist anymore lol
		if (vars.misc.cockblock)
		{
			if (ent->r.svFlags & SVF_CASTAI)
				return;
		}

		original::oBullet_Fire(ent, spread, damage);
	}

	void __cdecl hRE_RenderScene(const refdef_t* fd)
	{
		original::oRE_RenderScene(fd);

		//if you want to draw in main menu, you'll have to
		//reimplement original methods, since drawing code is stored in cgamex86.dll
		//and it's not loaded while not in-game
	}

	void __cdecl hRE_AddRefEntityToScene(const refEntity_t* refEnt)
	{
		refEntity_t* ent = const_cast<refEntity_t*>(refEnt);

		if (global::cls->state == CA_ACTIVE)
		{
			if (vars.visuals.wallhack)
			{
				gentity_t* g_ent = &global::g_entity[ent->entityNum];

				if (g_ent)
				{
					const char* name = g_ent->classname;

					if (strstr(name, "ai_"))
					{
						ent->hilightIntensity = 1.f;
						ent->renderfx |= RF_HILIGHT | RF_DEPTHHACK;
					}
				}
			}
		}

		original::oRE_AddRefEntityToScene(ent);
	}

	//ok, I can't actually say if this helps anything
	//but whatever lmao
	void __cdecl hR_BuildBones(mdsHeader_t* header, const refEntity_t* refent, int* boneList, int numBones)
	{
		const_cast<refEntity_t*>(refent)->reFlags |= REFLAG_FULL_LOD;

		header->lodScale = 1.f;
		header->lodBias = 0.f;

		static char* validBones = reinterpret_cast<char*>(0xA7F760);
		memset(validBones, 0, header->numBones);

		original::oR_BuildBones(header, refent, boneList, numBones);

		static mdsBoneFrame_t* oldBones = reinterpret_cast<mdsBoneFrame_t*>(0xA7C678);
		memset(oldBones, 0, sizeof(mdsBoneFrame_t) * header->numBones);
	}

	HMODULE __stdcall hLoadLibrary(LPCSTR lib_name)
	{
		HMODULE library = LoadLibraryA(lib_name);
		if (std::strstr(lib_name, "cgamex86") && library)
		{
			engine::com_printf("hooked cgamex86\n");
			hook_game_lib(1);
		}

		if (std::strstr(lib_name, "qagamex86") && library)
		{
			engine::com_printf("hooked qagamex86\n");
			hook_game_lib(0);
		}

		if (library)
			engine::com_printf("loaded %s\n", lib_name);

		return library;
	}

	//Because fucking discord would always prevent GetAsyncKeyState from working properly
	//if you're in voice chat
	//goddamn furry pedophiles can't even program for real, have to use electron, web monkeys
	//Also, if you "vid_restart", you need to re-hook the window
	LRESULT __stdcall hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_KEYDOWN:
			if (wParam == VK_INSERT)
			{
				global::is_opened = !global::is_opened;
			}
			if (global::is_opened && (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT))
				menu::handle_keys(wParam);
			break;
		default: break;
		}

		return CallWindowProc(original::oWndProc, hWnd, uMsg, wParam, lParam);
	}

	void init()
	{
		hooks::hook_iat("WolfSP.exe", "KERNEL32.dll", "LoadLibraryA", hooks::hLoadLibrary); //hook LoadLibrary, so we can monitor qa/cgame dll re-loading
		global::hwnd = FindWindowA("Wolfenstein", nullptr);

		original::oWndProc					= reinterpret_cast<WNDPROC>(SetWindowLong(global::hwnd, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::hWndProc)));
		original::oRE_AddRefEntityToScene	= reinterpret_cast<addrefent_t>		(DetourFunction(PBYTE(0x466AA0),	(PBYTE)hRE_AddRefEntityToScene));
		original::oRE_RenderScene			= reinterpret_cast<renderscene_t>	(DetourFunction(PBYTE(0x466D10),	(PBYTE)hRE_RenderScene));
		original::oCL_CreateNewCommands		= reinterpret_cast<newcommands_t>	(DetourFunction(PBYTE(0x408710),	(PBYTE)hCL_CreateNewCommands));
		original::oCL_WritePacket			= reinterpret_cast<writepacket_t>	(DetourFunction(PBYTE(0x408890),	(PBYTE)hCL_WritePacket));
		original::oCL_FinishMove			= reinterpret_cast<finishmove_t>	(DetourFunction(PBYTE(0x408550),	(PBYTE)hCL_FinishMove));
		original::oR_CalcBoneLerp			= reinterpret_cast<calcbone_t>		(DetourFunction(PBYTE(0x473740),	(PBYTE)0x00473E80)); //redirect CalcBoneLerp calls to CalcBone
		original::oR_BuildBones				= reinterpret_cast<buildbones_t>	(DetourFunction(PBYTE(0x474B70),	(PBYTE)hR_BuildBones));

		if (GetModuleHandle(L"qagamex86.dll"))
			hook_game_lib(0);

		if(GetModuleHandle(L"cgamex86.dll"))
			hook_game_lib(1);
	}

	void hook_game_lib(bool is_cgame)
	{
		if(is_cgame)
		{
			//hook cgamex86's functions
			original::oCG_Draw2D				= reinterpret_cast<draw2d_t>(DetourFunction(PBYTE(0x30009C10), PBYTE(hCG_Draw2D)));
			original::oCG_PredictPlayerState	= reinterpret_cast<predictstate_t>(DetourFunction(PBYTE(0x300346D0), PBYTE(hCG_PredictPlayerState)));
			original::oCG_Obituary				= reinterpret_cast<obituary_t>(DetourFunction(PBYTE(0x300194D0), PBYTE(hCG_Obituary)));
		}
		else
		{
			//hook qagamex86's functions
			original::oBullet_Fire_Extended		= reinterpret_cast<bullet_fire_ext_t>(DetourFunction(PBYTE(0x2006DD00), PBYTE(hBullet_Fire_Extended)));
			original::oBullet_Fire				= reinterpret_cast<bullet_fire_t>(DetourFunction(PBYTE(0x2006DCC0), PBYTE(hBullet_Fire)));
		}

	}

	//pasted
	//yes, no checks, the chad way
	void hook_iat(const char* iat_module_name, const char* import_module_name, const char* fn_name, void* new_fn)
	{
		auto module = (uintptr_t)GetModuleHandleA(iat_module_name);

		auto dos_header = (PIMAGE_DOS_HEADER)module;
		auto nt_headers = (PIMAGE_NT_HEADERS)(module + dos_header->e_lfanew);

		auto imports = (PIMAGE_IMPORT_DESCRIPTOR)(module + nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

		for (auto import = imports; import->Name; ++import) {
			auto module_name = (const char*)(module + import->Name);
			if (std::strcmp(module_name, import_module_name))
				continue;

			auto original_first_thunk = (PIMAGE_THUNK_DATA)(module + import->OriginalFirstThunk);
			auto first_thunk = (PIMAGE_THUNK_DATA)(module + import->FirstThunk);

			for (; original_first_thunk->u1.AddressOfData; ++original_first_thunk, ++first_thunk) {
				auto name = (const char*)((PIMAGE_IMPORT_BY_NAME)(module + original_first_thunk->u1.AddressOfData))->Name;
				if (std::strcmp(name, fn_name))
					continue;

				auto fn_address = &first_thunk->u1.Function;

				DWORD old;
				VirtualProtect(fn_address, sizeof(new_fn), PAGE_READWRITE, &old);
				*fn_address = (DWORD)new_fn;
				VirtualProtect(fn_address, sizeof(new_fn), old, &old);
				break;
			}

			break;
		}
	}
}