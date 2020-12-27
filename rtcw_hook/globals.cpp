#include "globals.h"

namespace global
{
	clientActive_t*		cl_active		= reinterpret_cast<clientActive_t*>	(0xF21260);
	level_locals_t*		level			= reinterpret_cast<level_locals_t*>	(0x20537000);
	centity_t*			cg_entities		= reinterpret_cast<centity_t*>		(0x305DDDE0);
	weaponInfo_t*		weapons			= reinterpret_cast<weaponInfo_t*>	(0x305BEE80);
	itemInfo_t*			items			= reinterpret_cast<itemInfo_t*>		(0x305BBFC0);
	gentity_t*			g_entity		= reinterpret_cast<gentity_t*>		(/*0x2056AF80*/ 0x2053EB80);
	cgs_t*				cgs				= reinterpret_cast<cgs_t*>			(0x3054E360);
	cg_t*				cg				= reinterpret_cast<cg_t*>			(0x30591FA0);
	pmove_t*			pm				= reinterpret_cast<pmove_t*>		(0x300E3238/*0x30A1D8F0*/);
	clientStatic_t*		cls				= reinterpret_cast<clientStatic_t*>	(0xEA15A0);
	kbutton_t*			kb				= reinterpret_cast<kbutton_t*>		(0x7FCA10);


	HWND				hwnd = NULL;
	bool is_opened = false;

}