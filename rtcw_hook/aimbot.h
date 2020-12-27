#pragma once
#include "q3types.h"
#include "framework.h"

namespace aimbot
{
	void			run();
	bool			can_aim();
	gentity_s*		get_target();
	void			nospread(usercmd_t*);
	void			fix_move(usercmd_t*);
	bool			is_visible(gentity_s* entity);
	bool			get_aim_angles(gentity_s* entity, vec3_t& angles);

	extern vec3_t	silent_angles;
	extern bool		has_active_target;
}