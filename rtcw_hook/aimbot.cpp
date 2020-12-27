#include "aimbot.h"
#include "variables.h"
#include "q3types.h"
#include "math.h"
#include "globals.h"
#include "funcs.h"

int *seed = reinterpret_cast<int*>(0x2009BE84);

namespace aimbot
{
	vec3_t	silent_angles = { 0,0,0 };
	bool	has_active_target = false;

	void run()
	{
		vec3_t angles		= {};

		silent_angles[0]	= 0;
		silent_angles[1]	= 0;

		if (!can_aim())
			return;

		auto entity = get_target();
		if (entity && get_aim_angles(entity, angles))
		{
			has_active_target = true;

			if (!vars.aimbot.silentaim)
			{
				global::cl_active->viewangles[0] = angles[0];
				global::cl_active->viewangles[1] = angles[1];

				//if it works, it works
				if (vars.aimbot.autofire) {
					engine::key_down(&global::kb[KB_BUTTONS0]);
					engine::key_up(&global::kb[KB_BUTTONS0]);
				}
			}
			else
			{
				silent_angles[0] = angles[0];
				silent_angles[1] = angles[1];
			}
		}
	}

	bool can_aim()
	{
		const auto state = global::pm->ps;
		if (state->weapon == WP_KNIFE || state->weapon == WP_TESLA || state->weapon == WP_PANZERFAUST)
			return false;

		if (state->weaponstate == WEAPON_RELOADING)
			return false;

		return true;
	}

	gentity_s* get_target()
	{
		has_active_target	= false;
		gentity_s*	temp	= nullptr;
		float	distance	= 999999.f;

		for (int i = 1; i < global::cgs->maxclients; i++)
		{
			gentity_t* entity = &global::g_entity[i];
			if (!entity || !(entity->r.svFlags & SVF_CASTAI))
				continue;

			if (entity->health <= 0 || !entity->inuse || entity->aiInactive)
				continue;

			//Nazi / Monster / Undead || or maybe just != 1 ?
			if (entity->aiTeam != 1 && is_visible(entity))
			{
				float temp_distance = math::distance(entity->s.origin, global::cl_active->snap.ps.origin);
				if (!distance || temp_distance < distance)
				{
					distance = temp_distance;
					temp = entity;
				}
			}
		}

		return temp;
	}

	//do later, bullet_fire hook is enough
	//this would be real nospread tho
	void nospread(usercmd_t* cmd)
	{

	}

	bool is_visible(gentity_s* entity)
	{
		trace_t tr				= {};
		orientation_t orient	= {};

		if (engine::cg_gettag(entity->s.number, "tag_head", &orient))
		{
			engine::cg_trace(&tr, global::cg->refdef.vieworg, NULL, NULL, orient.origin, 0, CONTENTS_SOLID);
			return (tr.fraction >= 0.97f || tr.entityNum == entity->s.number);
		}

		return false;
	}

	bool get_aim_angles(gentity_s* entity, vec3_t& angles)
	{
		vec3_t view_position	= {};
		vec3_t delta			= {};
		orientation_t orient	= {};

		if (!engine::cg_gettag(entity->s.number, "tag_head", &orient))
			return false;

		//"tag_head" is neck for some reason
		//let's aim at the actual head
		orient.origin[2] += 5.f;

		VectorCopy(global::cg->predictedPlayerState.origin, view_position);
		view_position[2] += global::cg->predictedPlayerState.viewheight;
		
		VectorSubtract(orient.origin, view_position, delta);

		math::vec_to_angle(delta, angles);

		angles[0] -= SHORT2ANGLE(global::cg->predictedPlayerState.delta_angles[0]);
		angles[1] -= SHORT2ANGLE(global::cg->predictedPlayerState.delta_angles[1]);
		angles[2] = 0;

		return true;
	}

	//creds: Twice @ uc
	void fix_move(usercmd_t* cmd)
	{
		if (cmd->forwardmove != 0 || cmd->rightmove != 0)
		{
			float move_angle	= math::normalize_360(RAD2DEG(atan2f(-cmd->rightmove / 127.0, cmd->forwardmove / 127.0)));
			float delta_angle	= math::normalize_360(aimbot::silent_angles[1] - (global::cg->predictedPlayerState.viewangles[1] - SHORT2ANGLE(global::cg->predictedPlayerState.delta_angles[1])));
			float dest_angle	= math::normalize_360(move_angle - delta_angle);

			float forwardmove_ratio = cosf(DEG2RAD(dest_angle));
			float rightmove_ratio = -sinf(DEG2RAD(dest_angle));

			if (abs(forwardmove_ratio) < abs(rightmove_ratio))
			{
				forwardmove_ratio *= 1.0f / abs(rightmove_ratio);
				rightmove_ratio = rightmove_ratio > 0.0f ? 1.0f : -1.0f;
			}
			else if (abs(forwardmove_ratio) > abs(rightmove_ratio))
			{
				rightmove_ratio *= 1.0f / abs(forwardmove_ratio);
				forwardmove_ratio = forwardmove_ratio > 0.0f ? 1.0f : -1.0f;
			}
			else
			{
				forwardmove_ratio = 1.0;
				rightmove_ratio = 1.0;
			}

			cmd->forwardmove = static_cast<signed char>(forwardmove_ratio * 127);
			cmd->rightmove = static_cast<signed char>(rightmove_ratio * 127);
		}
	}
}