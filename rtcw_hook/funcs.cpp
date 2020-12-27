#include "framework.h"
#include "aimbot.h"
#include "globals.h"
#include "variables.h"
#include "funcs.h"

namespace engine
{
	printf_t	com_printf				= reinterpret_cast<printf_t>(0x41B660);
	getcmd_t	cl_getusercmd			= reinterpret_cast<getcmd_t>(0x401040);
	findvar_t	cvar_findvar			= reinterpret_cast<findvar_t>(0x41E5E0);
	cvarget_t	cvar_get				= reinterpret_cast<cvarget_t>(0x41E720);
	cvarset_t	cvar_set				= reinterpret_cast<cvarset_t>(0x41E950);
	regshader_t re_registershader		= reinterpret_cast<regshader_t>(0x462440);

	addtext_t	cbuf_addtext			= reinterpret_cast<addtext_t>(0x41ACD0);

	gettag_t	cg_gettag				= reinterpret_cast<gettag_t>(0x30033590);
	drawtext_t	cg_drawstringext		= reinterpret_cast<drawtext_t>(0x3000D2A0);
	drawrect_t	cg_drawrect				= reinterpret_cast<drawrect_t>(0x3000D030);
	filledbar_t cg_filledbar			= reinterpret_cast<filledbar_t>(0x3000CBD0);
	fillrect_t	cg_fillrect				= reinterpret_cast<fillrect_t>(0x3000CB70);
	tracefn_t	cg_trace				= reinterpret_cast<tracefn_t>(0x30034300);

	inkey_t		key_down				= reinterpret_cast<inkey_t>(0x407890);
	inkey_t		key_up					= reinterpret_cast<inkey_t>(0x407910);

	void wr_drawstring(int x, int y, const float *setColor,
		qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars, const char* fmt, ...)
	{
		va_list vl;
		char buf[512] = { 0 };

		va_start(vl, fmt);
		vsprintf_s(buf, sizeof buf, fmt, vl);
		va_end(vl);

		cg_drawstringext(x, y, buf, setColor, forceColor, shadow, charWidth, charHeight, maxChars);
	}
}

namespace cheat
{
	bool world2screen(vec3_t pos, vec2_t &scr)
	{
		vec3_t trans;
		float xc, yc;
		float px, py;
		float z;

		px = tanf(global::cg->refdef.fov_x * (M_PI / 360));
		py = tanf(global::cg->refdef.fov_y * (M_PI / 360));

		VectorSubtract(pos, global::cg->refdef.vieworg, trans);

		xc = 640 / 2.0;
		yc = 480 / 2.0;

		// z = how far is the object in our forward direction
		z = DotProduct(trans, global::cg->refdef.viewaxis[0]);
		if (z <= 0.001)
			return qfalse;

		scr[0] = xc - DotProduct(trans, global::cg->refdef.viewaxis[1]) * xc / (z * px);
		scr[1] = yc - DotProduct(trans, global::cg->refdef.viewaxis[2]) * yc / (z * py);

		return qtrue;
	}

	bool w2swrap(vec3_t worldCoord, int* x, int* y)
	{
		vec2_t pos;

		if (world2screen(worldCoord, pos)) {
			*x = (int)pos[0];
			*y = (int)pos[1];
			return qtrue;
		}

		return qfalse;
	}

	void debug()
	{
		//draw stuff for debugging

	}

	void esp()
	{		
		int x, y;
		float clr[4] = { 0.65f, 1.f, 0.f, 1.f };
		float clr2[4] = { 1.f, 0.f, 0.f, 1.f };

		trace_t tr;
		orientation_t orient;

		for (int i = 0; i < MAX_ENTITIES; i++)
		{
			gentity_t* entity = &global::g_entity[i];
			if(!entity || !(entity->r.svFlags & SVF_CASTAI))
				continue;

			if(entity->health <= 0 || !entity->inuse || entity->aiInactive)
				continue;

			if (w2swrap(entity->s.pos.trBase, &x, &y))
			{
				engine::wr_drawstring(x, y, clr, qtrue, qfalse, 3, 4, 24, "%s", entity->classname);
				engine::wr_drawstring(x, y + 4, clr, qtrue, qfalse, 3, 4, 24, "%d", entity->health);
			}

			if (engine::cg_gettag(entity->s.clientNum, "tag_head", &orient))
			{
				if (w2swrap(orient.origin, &x, &y))
				{
					engine::cg_trace(&tr, global::cg->refdef.vieworg, NULL, NULL, orient.origin, 0, CONTENTS_SOLID);

					bool visible = (tr.fraction >= 0.97f || tr.entityNum == entity->s.clientNum);

					engine::wr_drawstring(x, y, visible ? clr2 : clr, qtrue, qfalse, 5, 5, 1, "*");
				}
			}
		}
	}
}