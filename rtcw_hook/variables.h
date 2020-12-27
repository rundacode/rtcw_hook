#pragma once
#include "q3types.h"

struct variables
{
	struct
	{
		int enabled = false;
		int silentaim = false;
		int autofire = false;
	} aimbot;

	struct
	{
		int wallhack = false;
		int fov = 140;
		int esp = 0;
	} visuals;

	struct
	{
		int norecoil = false;
		int nospread = false;
		int nooverheat = false;
		int infammo = false;
		int rapidfire = false;
		int highdamage = false;
	} weapons;

	struct
	{
		int speedhack = false;
		int bunnyhop = false;
		int cockblock = false;

		int shfactor = 1;
	} misc;
};

struct convars
{
	cvar_t* aim_enabled		= nullptr;
	cvar_t* aim_silent		= nullptr;
	cvar_t* aim_autofire	= nullptr;

	cvar_t* vis_wallhack = nullptr;
	//cvar_t* vis_fov = nullptr; //not needed? we have cg_fov already

	cvar_t* wep_nospread = nullptr;
	cvar_t* wep_norecoil = nullptr;
	cvar_t* wep_infammo = nullptr;
};

extern variables vars;
extern convars cvars;