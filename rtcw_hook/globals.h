#pragma once
#include "q3types.h"
#include "framework.h"

namespace global
{
	extern clientActive_t*		cl_active;
	extern level_locals_t*		level;
	extern usercmd_t*			current_cmd;
	extern centity_t*			cg_entities;
	extern weaponInfo_t*		weapons;
	extern itemInfo_t*			items;
	extern gentity_t*			g_entity;
	extern cgs_t*				cgs;
	extern cg_t*				cg;
	extern pmove_t*				pm;
	extern clientStatic_t*		cls;
	extern kbutton_t*			kb;

	extern HWND	hwnd;
	extern bool is_opened;

}