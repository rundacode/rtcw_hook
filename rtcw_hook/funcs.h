#pragma once

#include "q3types.h"

#define BAR_LEFT        0x0001
#define BAR_CENTER      0x0002
#define BAR_VERT        0x0004
#define BAR_NOHUDALPHA  0x0008
#define BAR_BG          0x0010
// different spacing modes for use w/ BAR_BG
#define BAR_BGSPACING_X0Y5  0x0020
#define BAR_BGSPACING_X0Y0  0x0040

#define BAR_LERP_COLOR  0x0100

//typedefs for game funcs

using printf_t = void(__cdecl*)(const char*, ...);
using drawtext_t = void(__cdecl*)(int x, int y, const char *string, const float *setColor,
	qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars);
using fillrect_t = void(__cdecl*)(float x, float y, float width, float height, const float *color);
using drawrect_t = void(__cdecl*)(float x, float y, float width, float height, float size, const float *color);
using filledbar_t = void(__cdecl*)(float x, float y, float w, float h, const float *startColorIn, float *endColor, const float *bgColor, float frac, int flags);
using addtext_t = void(__cdecl*)(const char* cmd);
using regshader_t = qhandle_t(__cdecl*)(const char* name);

using gettag_t = qboolean(__cdecl*)(int clNum, const char* tagName, orientation_t* orient);

using getcmd_t = qboolean(__cdecl*)(int num, usercmd_t* cmd);

using tracefn_t = void(__cdecl*)(trace_t *result, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end,
	int skipNumber, int mask);

using findvar_t = cvar_t * (__cdecl*)(const char*);

using cvarget_t = cvar_t * (__cdecl*)(const char* var, const char* val, int flags);
using cvarset_t = cvar_t * (__cdecl*)(const char* var, const char* val, qboolean force);

using inkey_t = void(__cdecl*)(kbutton_t* b);

namespace engine
{
	extern printf_t com_printf;
	extern getcmd_t cl_getusercmd;
	extern gettag_t cg_gettag;
	extern tracefn_t cg_trace;
	extern addtext_t cbuf_addtext;
	extern regshader_t re_registershader;

	extern findvar_t cvar_findvar;
	extern cvarget_t cvar_get;
	extern cvarset_t cvar_set;

	extern inkey_t key_down;
	extern inkey_t key_up;

	extern drawtext_t cg_drawstringext;
	extern fillrect_t cg_fillrect;
	extern drawrect_t cg_drawrect;
	extern filledbar_t cg_filledbar;

	void wr_drawstring(int x, int y, const float *setColor,
		qboolean forceColor, qboolean shadow, int charWidth, int charHeight, int maxChars, const char* fmt, ...);
}

namespace cheat
{
	void esp();
	void debug();
	void* get_model(qhandle_t index);
}