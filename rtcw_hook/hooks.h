#pragma once
#include "q3types.h"

using predictstate_t		= void(__cdecl*)(void);
using draw2d_t				= void(__cdecl*)(void);
using newcommands_t			= void(__cdecl*)(void);
using writepacket_t			= void(__cdecl*)(void);
using setcolor_t			= void(__cdecl*)(const float* rgba);
using obituary_t			= void(__cdecl*)(entityState_t*);
using bullet_fire_ext_t		= void(__cdecl*)(gentity_t*, gentity_t*, vec3_t, vec3_t, float, int, int);
using bullet_fire_t			= void(__cdecl*)(gentity_t*, float, int );
using finishmove_t			= void(__cdecl*)(usercmd_t*);
using wndproc_t				= LRESULT(__stdcall*)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
using addrefent_t			= void(__cdecl*)(const refEntity_t*);
using renderscene_t			= void(__cdecl*)(const refdef_t* fd);
using buildbones_t			= void(__cdecl*)(mdsHeader_t* header, const refEntity_t* refent, int* boneList, int numBones);
using calcbone_t			= void(__cdecl*)(mdsHeader_t* header, const refEntity_t* refent, int boneNum);

namespace hooks
{
	void init();
	void hook_game_lib(bool);

	void __cdecl hCL_FinishMove(usercmd_t*);
	void __cdecl hBullet_Fire(gentity_t*, float, int);
	void __cdecl hCG_PredictPlayerState();
	void __cdecl hCL_CreateNewCommands();
	void __cdecl hCG_Draw2D();
	//void __cdecl hRE_SetColor(const float* rgba);
	void __cdecl hCG_Obituary(entityState_t* ent);
	void __cdecl hCL_WritePacket();
	void __cdecl hBullet_Fire_Extended(gentity_t *source, gentity_t *attacker, vec3_t start, vec3_t end, float spread, int damage, int recursion);
	void __cdecl hRE_AddRefEntityToScene(const refEntity_t*);
	void __cdecl hRE_RenderScene(const refdef_t* fd);
	void __cdecl hR_BuildBones(mdsHeader_t* header, const refEntity_t* refent, int* boneList, int numBones);

	LRESULT __stdcall hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void hook_iat(const char* iat_module_name, const char* import_module_name, const char* fn_name, void* new_fn);

	HMODULE __stdcall hLoadLibrary(LPCSTR);

	namespace original
	{
		extern predictstate_t		oCG_PredictPlayerState;
		extern draw2d_t				oCG_Draw2D;
		extern bullet_fire_ext_t	oBullet_Fire_Extended;
		extern newcommands_t		oCL_CreateNewCommands;
		extern bullet_fire_t		oBullet_Fire;
		extern finishmove_t			oCL_FinishMove;
		extern obituary_t			oCG_Obituary;
		extern wndproc_t			oWndProc;
		extern writepacket_t		oCL_WritePacket;
		extern renderscene_t		oRE_RenderScene;
		extern addrefent_t			oRE_AddRefEntityToScene;
		extern buildbones_t			oR_BuildBones;
		extern calcbone_t			oR_CalcBoneLerp; //we won't use this
		extern setcolor_t			oR_SetColor;
	}
}