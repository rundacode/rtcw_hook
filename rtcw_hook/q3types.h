#pragma once

/*
RTCW Hook :: All-in-One definitions header

Credits: RTCW Source Code (idSoftware, Raven Software)
*/


#define DEG2RAD( a )					( ( ( a ) * M_PI ) / 180.0F )
#define RAD2DEG( a )					( ( ( a ) * 180.0f ) / M_PI )

typedef unsigned char byte;

#define CMD_BACKUP          64
#define CMD_MASK            ( CMD_BACKUP - 1 )

typedef enum { qfalse, qtrue }    qboolean;

typedef int qhandle_t;
typedef int sfxHandle_t;
typedef int fileHandle_t;
typedef int clipHandle_t;

// RF, this is just here so different elements of the engine can be aware of this setting as it changes
#define MAX_SP_CLIENTS      64      // increasing this will increase memory usage significantly

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define MAX_STRING_CHARS    1024    // max length of a string passed to Cmd_TokenizeString
#define MAX_STRING_TOKENS   256     // max tokens resulting from Cmd_TokenizeString
#define MAX_TOKEN_CHARS     1024    // max length of an individual token

#define MAX_INFO_STRING     1024
#define MAX_INFO_KEY        1024
#define MAX_INFO_VALUE      1024

#define BIG_INFO_STRING     8192    // used for system info key only
#define BIG_INFO_KEY        8192
#define BIG_INFO_VALUE      8192

#define MAX_QPATH           64      // max length of a quake game pathname
#define MAX_OSPATH          256     // max length of a filesystem pathname

#define MAX_NAME_LENGTH     32      // max length of a client name

#define MAX_SAY_TEXT        150

#define GAME_API_VERSION    8

// entity->svFlags
// the server does not know how to interpret most of the values
// in entityStates (level eType), so the game must explicitly flag
// special server behaviors
#define SVF_NOCLIENT            0x00000001  // don't send entity to clients, even if it has effects
#define SVF_VISDUMMY            0x00000004  // this ent is a "visibility dummy" and needs it's master to be sent to clients that can see it even if they can't see the master ent
#define SVF_BOT                 0x00000008
// Wolfenstein
#define SVF_CASTAI              0x00000010
// done.
#define SVF_BROADCAST           0x00000020  // send to all connected clients
#define SVF_PORTAL              0x00000040  // merge a second pvs at origin2 into snapshots
#define SVF_USE_CURRENT_ORIGIN  0x00000080  // entity->r.currentOrigin instead of entity->s.origin
											// for link position (missiles and movers)
// Ridah
#define SVF_NOFOOTSTEPS         0x00000100
// done.
// MrE:
#define SVF_CAPSULE             0x00000200  // use capsule for collision detection

#define SVF_VISDUMMY_MULTIPLE   0x00000400  // so that one vis dummy can add to snapshot multiple speakers

// recent id changes
#define SVF_SINGLECLIENT        0x00000800  // only send to a single client (entityShared_t->singleClient)
#define SVF_NOSERVERINFO        0x00001000  // don't send CS_SERVERINFO updates to this client
											// so that it can be updated for ping tools without
											// lagging clients
#define SVF_NOTSINGLECLIENT     0x00002000  // send entity to everyone but one client
											// (entityShared_t->singleClient)

// paramters for command buffer stuffing
typedef enum {
	EXEC_NOW,           // don't return until completed, a VM should NEVER use this,
						// because some commands might cause the VM to be unloaded...
						EXEC_INSERT,        // insert at current position, but don't run yet
						EXEC_APPEND         // add to end of the command buffer (normal case)
} cbufExec_t;


//
// these aren't needed by any of the VMs.  put in another header?
//
#define MAX_MAP_AREA_BYTES      32      // bit vector of area visibility


// print levels from renderer (FIXME: set up for game / cgame?)
typedef enum {
	PRINT_ALL,
	PRINT_DEVELOPER,        // only print when "developer 1"
	PRINT_WARNING,
	PRINT_ERROR
} printParm_t;


typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];
typedef vec_t vec5_t[5];

typedef int fixed4_t;
typedef int fixed8_t;
typedef int fixed16_t;

#ifndef M_PI
#define M_PI        3.14159265358979323846f // matches value in gcc v2 math.h
#endif

#define DotProduct( x,y )         ( ( x )[0] * ( y )[0] + ( x )[1] * ( y )[1] + ( x )[2] * ( y )[2] )
#define VectorSubtract( a,b,c )   ( ( c )[0] = ( a )[0] - ( b )[0],( c )[1] = ( a )[1] - ( b )[1],( c )[2] = ( a )[2] - ( b )[2] )
#define VectorAdd( a,b,c )        ( ( c )[0] = ( a )[0] + ( b )[0],( c )[1] = ( a )[1] + ( b )[1],( c )[2] = ( a )[2] + ( b )[2] )
#define VectorCopy( a,b )         ( ( b )[0] = ( a )[0],( b )[1] = ( a )[1],( b )[2] = ( a )[2] )
#define VectorCopy4( a,b )        ( ( b )[0] = ( a )[0],( b )[1] = ( a )[1],( b )[2] = ( a )[2],( b )[3] = ( a )[3] )
#define VectorScale( v, s, o )    ( ( o )[0] = ( v )[0] * ( s ),( o )[1] = ( v )[1] * ( s ),( o )[2] = ( v )[2] * ( s ) )
#define VectorMA( v, s, b, o )    ( ( o )[0] = ( v )[0] + ( b )[0] * ( s ),( o )[1] = ( v )[1] + ( b )[1] * ( s ),( o )[2] = ( v )[2] + ( b )[2] * ( s ) )

#define VectorClear( a )              ( ( a )[0] = ( a )[1] = ( a )[2] = 0 )
#define VectorNegate( a,b )           ( ( b )[0] = -( a )[0],( b )[1] = -( a )[1],( b )[2] = -( a )[2] )
#define VectorSet( v, x, y, z )       ( ( v )[0] = ( x ), ( v )[1] = ( y ), ( v )[2] = ( z ) )

#define Vector4Set( v, x, y, z, n )   ( ( v )[0] = ( x ),( v )[1] = ( y ),( v )[2] = ( z ),( v )[3] = ( n ) )
#define Vector4Copy( a,b )            ( ( b )[0] = ( a )[0],( b )[1] = ( a )[1],( b )[2] = ( a )[2],( b )[3] = ( a )[3] )
#define Vector4MA( v, s, b, o )       ( ( o )[0] = ( v )[0] + ( b )[0] * ( s ),( o )[1] = ( v )[1] + ( b )[1] * ( s ),( o )[2] = ( v )[2] + ( b )[2] * ( s ),( o )[3] = ( v )[3] + ( b )[3] * ( s ) )
#define Vector4Average( v, b, s, o )  ( ( o )[0] = ( ( v )[0] * ( 1 - ( s ) ) ) + ( ( b )[0] * ( s ) ),( o )[1] = ( ( v )[1] * ( 1 - ( s ) ) ) + ( ( b )[1] * ( s ) ),( o )[2] = ( ( v )[2] * ( 1 - ( s ) ) ) + ( ( b )[2] * ( s ) ),( o )[3] = ( ( v )[3] * ( 1 - ( s ) ) ) + ( ( b )[3] * ( s ) ) )

#define SnapVector( v ) {v[0] = ( (int)( v[0] ) ); v[1] = ( (int)( v[1] ) ); v[2] = ( (int)( v[2] ) );}

// mode parm for FS_FOpenFile
typedef enum {
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPEND_SYNC
} fsMode_t;

typedef enum {
	FS_SEEK_CUR,
	FS_SEEK_END,
	FS_SEEK_SET
} fsOrigin_t;

typedef struct
{
	byte b0;
	byte b1;
	byte b2;
	byte b3;
	byte b4;
	byte b5;
	byte b6;
	byte b7;
} qint64;

#define CVAR_ARCHIVE        1   // set to cause it to be saved to vars.rc
// used for system variables, not for player
// specific configurations
#define CVAR_USERINFO       2   // sent to server on connect or change
#define CVAR_SERVERINFO     4   // sent in response to front end requests
#define CVAR_SYSTEMINFO     8   // these cvars will be duplicated on all clients
#define CVAR_INIT           16  // don't allow change from console at all,
								// but can be set from the command line
#define CVAR_LATCH          32  // will only change when C code next does
								// a Cvar_Get(), so it can't be changed
								// without proper initialization.  modified
								// will be set, even though the value hasn't
								// changed yet
#define CVAR_ROM            64  // display only, cannot be set by user at all
#define CVAR_USER_CREATED   128 // created by a set command
#define CVAR_TEMP           256 // can be set even when cheats are disabled, but is not archived
#define CVAR_CHEAT          512 // can not be changed if cheats are disabled
#define CVAR_NORESTART      1024    // do not clear when a cvar_restart is issued

typedef struct cvar_s {
	char        *name;
	char        *string;
	char        *resetString;       // cvar_restart will reset to this value
	char        *latchedString;     // for CVAR_LATCH vars
	int flags;
	qboolean modified;              // set each time the cvar is changed
	int modificationCount;          // incremented each time the cvar is changed
	float value;                    // atof( string )
	int integer;                    // atoi( string )
	struct cvar_s *next;
	struct cvar_s *hashNext;
} cvar_t;

#define MAX_CVAR_VALUE_STRING   256

typedef int cvarHandle_t;

// the modules that run in the virtual machine can't access the cvar_t directly,
// so they must ask for structured updates
typedef struct {
	cvarHandle_t handle;
	int modificationCount;
	float value;
	int integer;
	char string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;

typedef struct cplane_s {
	vec3_t normal;
	float dist;
	byte type;              // for fast side tests: 0,1,2 = axial, 3 = nonaxial
	byte signbits;          // signx + (signy<<1) + (signz<<2), used as lookup during collision
	byte pad[2];
} cplane_t;

// a trace is returned when a box is swept through the world
typedef struct {
	qboolean allsolid;      // if true, plane is not valid
	qboolean startsolid;    // if true, the initial point was in a solid area
	float fraction;         // time completed, 1.0 = didn't hit anything
	vec3_t endpos;          // final position
	cplane_t plane;         // surface normal at impact, transformed to world space
	int surfaceFlags;           // surface hit
	int contents;           // contents on other side of surface hit
	int entityNum;          // entity the contacted sirface is a part of
} trace_t;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD


// markfragments are returned by CM_MarkFragments()
typedef struct {
	int firstPoint;
	int numPoints;
} markFragment_t;

typedef struct {
	vec3_t origin;
	vec3_t axis[3];
} orientation_t;

typedef enum {
	CHAN_AUTO,
	CHAN_LOCAL,     // menu sounds, etc
	CHAN_WEAPON,
	CHAN_VOICE,
	CHAN_ITEM,
	CHAN_BODY,
	CHAN_LOCAL_SOUND,   // chat messages, etc
	CHAN_ANNOUNCER      // announcer voices, etc
} soundChannel_t;
#define ANIM_BITS       10

#define ANGLE2SHORT( x )  ( (int)( ( x ) * 65536 / 360 ) & 65535 )
#define SHORT2ANGLE( x )  ( ( x ) * ( 360.0f / 65536 ) )

#define SNAPFLAG_RATE_DELAYED   1
#define SNAPFLAG_NOT_ACTIVE     2   // snapshot used during connection and for zombies
#define SNAPFLAG_SERVERCOUNT    4   // toggled every map_restart so transitions can be detected

// content masks
#define MASK_ALL                ( -1 )
#define MASK_SOLID              ( CONTENTS_SOLID )
#define MASK_PLAYERSOLID        ( CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_BODY )
#define MASK_DEADSOLID          ( CONTENTS_SOLID | CONTENTS_PLAYERCLIP )
#define MASK_WATER              ( CONTENTS_WATER | CONTENTS_LAVA | CONTENTS_SLIME )
//#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define MASK_OPAQUE             ( CONTENTS_SOLID | CONTENTS_LAVA )      //----(SA)	modified since slime is no longer deadly
#define MASK_SHOT               ( CONTENTS_SOLID | CONTENTS_BODY | CONTENTS_CORPSE | CONTENTS_CLIPSHOT )
#define MASK_MISSILESHOT        ( MASK_SHOT | CONTENTS_MISSILECLIP )
#define MASK_AISIGHT            ( CONTENTS_SOLID | CONTENTS_AI_NOSIGHT )


//
// per-level limits
//
#define MAX_CLIENTS         128     // absolute limit
#define MAX_LOCATIONS       64

#define GENTITYNUM_BITS     10      // don't need to send any more
//#define	GENTITYNUM_BITS		11		// don't need to send any more		(SA) upped 4/21/2001 adjusted: tr_local.h (802-822), tr_main.c (1501), sv_snapshot (206)
#define MAX_GENTITIES       ( 1 << GENTITYNUM_BITS )

// entitynums are communicated with GENTITY_BITS, so any reserved
// values thatare going to be communcated over the net need to
// also be in this range
#define ENTITYNUM_NONE      ( MAX_GENTITIES - 1 )
#define ENTITYNUM_WORLD     ( MAX_GENTITIES - 2 )
#define ENTITYNUM_MAX_NORMAL    ( MAX_GENTITIES - 2 )


#define MAX_MODELS          256     // these are sent over the net as 8 bits
#define MAX_SOUNDS          256     // so they cannot be blindly increased


#define MAX_PARTICLES_AREAS     128

#define MAX_MULTI_SPAWNTARGETS  16 // JPW NERVE

//#define	MAX_CONFIGSTRINGS	1024
#define MAX_CONFIGSTRINGS   2048

#define MAX_DLIGHT_CONFIGSTRINGS    128
#define MAX_CLIPBOARD_CONFIGSTRINGS 64
#define MAX_SPLINE_CONFIGSTRINGS    64

#define PARTICLE_SNOW128    1
#define PARTICLE_SNOW64     2
#define PARTICLE_SNOW32     3
#define PARTICLE_SNOW256    0

#define PARTICLE_BUBBLE8    4
#define PARTICLE_BUBBLE16   5
#define PARTICLE_BUBBLE32   6
#define PARTICLE_BUBBLE64   7

// these are the only configstrings that the system reserves, all the
// other ones are strictly for servergame to clientgame communication
#define CS_SERVERINFO       0       // an info string with all the serverinfo cvars
#define CS_SYSTEMINFO       1       // an info string for server system to client system configuration (timescale, etc)

#define RESERVED_CONFIGSTRINGS  2   // game can't modify below this, only the system can

#define MAX_GAMESTATE_CHARS 16000
typedef struct {
	int stringOffsets[MAX_CONFIGSTRINGS];
	char stringData[MAX_GAMESTATE_CHARS];
	int dataCount;
} gameState_t;

typedef enum
{
	AISTATE_RELAXED,
	AISTATE_QUERY,
	AISTATE_ALERT,
	AISTATE_COMBAT,

	MAX_AISTATES
} aistateEnum_t;

// bit field limits
#define MAX_STATS               16
#define MAX_PERSISTANT          16
#define MAX_POWERUPS            16
#define MAX_WEAPONS             64  // (SA) and yet more!
#define MAX_HOLDABLE            16

#define MAX_EVENTS              4   // max events per frame before we drop events

// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur

// you can't add anything to this without modifying the code in msg.c

// playerState_t is a full superset of entityState_t as it is used by players,
// so if a playerState_t is transmitted, the entityState_t can be fully derived
// from it.
//
// NOTE: all fields in here must be 32 bits (or those within sub-structures)
typedef struct playerState_s {
	int commandTime;            // cmd->serverTime of last executed command
	int pm_type;
	int bobCycle;               // for view bobbing and footstep generation
	int pm_flags;               // ducked, jump_held, etc
	int pm_time;

	vec3_t origin;
	vec3_t velocity;
	int weaponTime;
	int weaponDelay;            // for weapons that don't fire immediately when 'fire' is hit (grenades, venom, ...)
	int grenadeTimeLeft;            // for delayed grenade throwing.  this is set to a #define for grenade
									// lifetime when the attack button goes down, then when attack is released
									// this is the amount of time left before the grenade goes off (or if it
									// gets to 0 while in players hand, it explodes)


	int gravity;
	float leanf;                // amount of 'lean' when player is looking around corner //----(SA)	added

	int speed;
	int delta_angles[3];            // add to command angles to get view direction
									// changed by spawns, rotating objects, and teleporters

	int groundEntityNum;        // ENTITYNUM_NONE = in air

	int legsTimer;              // don't change low priority animations until this runs out
	int legsAnim;               // mask off ANIM_TOGGLEBIT

	int torsoTimer;             // don't change low priority animations until this runs out
	int torsoAnim;              // mask off ANIM_TOGGLEBIT

	int movementDir;            // a number 0 to 7 that represents the reletive angle
								// of movement to the view angle (axial and diagonals)
								// when at rest, the value will remain unchanged
								// used to twist the legs during strafing



	int eFlags;                 // copied to entityState_t->eFlags

	int eventSequence;          // pmove generated events
	int events[MAX_EVENTS];
	int eventParms[MAX_EVENTS];
	int oldEventSequence;           // so we can see which events have been added since we last converted to entityState_t

	int externalEvent;          // events set on player from another source
	int externalEventParm;
	int externalEventTime;

	int clientNum;              // ranges from 0 to MAX_CLIENTS-1

	// weapon info
	int weapon;                 // copied to entityState_t->weapon
	int weaponstate;

	// item info
	int item;

	vec3_t viewangles;          // for fixed views
	int viewheight;

	// damage feedback
	int damageEvent;            // when it changes, latch the other parms
	int damageYaw;
	int damagePitch;
	int damageCount;

	int stats[MAX_STATS];
	int persistant[MAX_PERSISTANT];         // stats that aren't cleared on death
	int powerups[MAX_POWERUPS];         // level.time that the powerup runs out
	int ammo[MAX_WEAPONS];              // total amount of ammo
	int ammoclip[MAX_WEAPONS];          // ammo in clip
	int holdable[MAX_HOLDABLE];
	int holding;                        // the current item in holdable[] that is selected (held)
	int weapons[MAX_WEAPONS / (sizeof(int) * 8)];   // 64 bits for weapons held

	// Ridah, allow for individual bounding boxes
	vec3_t mins, maxs;
	float crouchMaxZ;
	float crouchViewHeight, standViewHeight, deadViewHeight;
	// variable movement speed
	float runSpeedScale, sprintSpeedScale, crouchSpeedScale;
	// done.

	// Ridah, view locking for mg42
	int viewlocked;
	int viewlocked_entNum;

	// Ridah, need this to fix friction problems with slow zombie's whereby
	// the friction prevents them from accelerating to their full potential
	float friction;

	// Ridah, AI character id is used for weapon association
	int aiChar;
	int teamNum;

	// Rafael
	int gunfx;

	// RF, burning effect is required for view blending effect
	int onFireStart;

	int serverCursorHint;               // what type of cursor hint the server is dictating
	int serverCursorHintVal;            // a value (0-255) associated with the above

	trace_t serverCursorHintTrace;      // not communicated over net, but used to store the current server-side cursorhint trace

	// ----------------------------------------------------------------------
	// not communicated over the net at all
	// FIXME: this doesn't get saved between predicted frames on the clients-side (cg.predictedPlayerState)
	// So to use persistent variables here, which don't need to come from the server,
	// we could use a marker variable, and use that to store everything after it
	// before we read in the new values for the predictedPlayerState, then restore them
	// after copying the structure recieved from the server.

	// (SA) yeah.  this is causing me a little bit of trouble too.  can we go ahead with the above suggestion or find an alternative?

	int ping;                   // server to game info for scoreboard
	int pmove_framecount;           // FIXME: don't transmit over the network
	int entityEventSequence;

	int sprintTime;
	int sprintExertTime;

	// JPW NERVE -- value for all multiplayer classes with regenerating "class weapons" -- ie LT artillery, medic medpack, engineer build points, etc
	int classWeaponTime;
	int jumpTime;         // used in SP/MP to prevent jump accel
	// jpw

	int weapAnimTimer;              // don't change low priority animations until this runs out
	int weapAnim;               // mask off ANIM_TOGGLEBIT

	qboolean releasedFire;

	float aimSpreadScaleFloat;          // (SA) the server-side aimspreadscale that lets it track finer changes but still only
										// transmit the 8bit int to the client
	int aimSpreadScale;         // 0 - 255 increases with angular movement
	int lastFireTime;           // used by server to hold last firing frame briefly when randomly releasing trigger (AI)

	int quickGrenTime;

	int leanStopDebounceTime;

	int weapHeat[MAX_WEAPONS];          // some weapons can overheat.  this tracks (server-side) how hot each weapon currently is.
	int curWeapHeat;                    // value for the currently selected weapon (for transmission to client)

	int venomTime;

	//----(SA)	added
	int accShowBits;            // RF (changed from short), these should all be 32 bit
	int accHideBits;
	//----(SA)	end

	aistateEnum_t aiState;

	float footstepCount;

} playerState_t;


//====================================================================


//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions
//
#define BUTTON_ATTACK       1
#define BUTTON_TALK         2           // displays talk balloon and disables actions
#define BUTTON_USE_HOLDABLE 4
#define BUTTON_GESTURE      8
#define BUTTON_WALKING      16          // walking can't just be infered from MOVE_RUN
										// because a key pressed late in the frame will
										// only generate a small move value for that frame
										// walking will use different animations and
										// won't generate footsteps
//----(SA)	added
#define BUTTON_SPRINT       32
#define BUTTON_ACTIVATE     64
//----(SA)	end

#define BUTTON_ANY          128         // any key whatsoever




//----(SA) wolf buttons
#define WBUTTON_ATTACK2     1
#define WBUTTON_ZOOM        2
#define WBUTTON_QUICKGREN   4
#define WBUTTON_RELOAD      8
#define WBUTTON_LEANLEFT    16
#define WBUTTON_LEANRIGHT   32

// unused
#define WBUTTON_EXTRA6      64
#define WBUTTON_EXTRA7      128
//----(SA) end

#define MOVE_RUN            120         // if forwardmove or rightmove are >= MOVE_RUN,
										// then BUTTON_WALKING should be set


// usercmd_t is sent to the server each client frame
typedef struct usercmd_s {
	int serverTime;
	byte buttons;
	byte wbuttons;
	byte weapon;
	byte holdable;          //----(SA)	added
	int angles[3];


	signed char forwardmove, rightmove, upmove;
	signed char wolfkick;       // RF, we should move this over to a wbutton, this is a huge waste of bandwidth

	unsigned short cld;         // NERVE - SMF - send client damage in usercmd instead of as a server command
} usercmd_t;

//===================================================================

// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define SOLID_BMODEL    0xffffff

typedef enum {
	TR_STATIONARY,
	TR_INTERPOLATE,             // non-parametric, but interpolate between snapshots
	TR_LINEAR,
	TR_LINEAR_STOP,
	TR_LINEAR_STOP_BACK,        //----(SA)	added.  so reverse movement can be different than forward
	TR_SINE,                    // value = base + sin( time / duration ) * delta
	TR_GRAVITY,
	// Ridah
	TR_GRAVITY_LOW,
	TR_GRAVITY_FLOAT,           // super low grav with no gravity acceleration (floating feathers/fabric/leaves/...)
	TR_GRAVITY_PAUSED,          //----(SA)	has stopped, but will still do a short trace to see if it should be switched back to TR_GRAVITY
	TR_ACCELERATE,
	TR_DECCELERATE
} trType_t;

typedef struct {
	trType_t trType;
	int trTime;
	int trDuration;             // if non 0, trTime + trDuration = stop time
//----(SA)	removed
	vec3_t trBase;
	vec3_t trDelta;             // velocity, etc
//----(SA)	removed
} trajectory_t;

// RF, put this here so we have a central means of defining a Zombie (kind of a hack, but this is to minimize bandwidth usage)
#define SET_FLAMING_ZOMBIE( x,y ) ( x.frame = y )
#define IS_FLAMING_ZOMBIE( x )    ( x.frame == 1 )

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large
//
// NOTE: all fields in here must be 32 bits (or those within sub-structures)

typedef struct entityState_s {
	int number;             // entity index
	int eType;              // entityType_t
	int eFlags;

	trajectory_t pos;       // for calculating position
	trajectory_t apos;      // for calculating angles

	int time;
	int time2;

	vec3_t origin;
	vec3_t origin2;

	vec3_t angles;
	vec3_t angles2;

	int otherEntityNum;     // shotgun sources, etc
	int otherEntityNum2;

	int groundEntityNum;        // -1 = in air

	int constantLight;      // r + (g<<8) + (b<<16) + (intensity<<24)
	int dl_intensity;       // used for coronas
	int loopSound;          // constantly loop this sound

	int modelindex;
	int modelindex2;
	int clientNum;          // 0 to (MAX_CLIENTS - 1), for players and corpses
	int frame;

	int solid;              // for client side prediction, trap_linkentity sets this properly

	// old style events, in for compatibility only
	int event;
	int eventParm;

	int eventSequence;      // pmove generated events
	int events[MAX_EVENTS];
	int eventParms[MAX_EVENTS];

	// for players
	int powerups;           // bit flags
	int weapon;             // determines weapon and flash model, etc
	int legsAnim;           // mask off ANIM_TOGGLEBIT
	int torsoAnim;          // mask off ANIM_TOGGLEBIT
//	int		weapAnim;		// mask off ANIM_TOGGLEBIT	//----(SA)	removed (weap anims will be client-side only)

	int density;            // for particle effects

	int dmgFlags;           // to pass along additional information for damage effects for players/ Also used for cursorhints for non-player entities

	// Ridah
	int onFireStart, onFireEnd;

	int aiChar, teamNum;

	int effect1Time, effect2Time, effect3Time;

	aistateEnum_t aiState;

	int animMovetype;       // clients can't derive movetype of other clients for anim scripting system


} entityState_t;

typedef enum {
	CA_UNINITIALIZED,
	CA_DISCONNECTED,    // not talking to a server
	CA_AUTHORIZING,     // not used any more, was checking cd key
	CA_CONNECTING,      // sending request packets to the server
	CA_CHALLENGING,     // sending challenge packets to the server
	CA_CONNECTED,       // netchan_t established, getting gamestate
	CA_LOADING,         // only during cgame initialization, never during main loop
	CA_PRIMED,          // got gamestate, waiting for first frame
	CA_ACTIVE,          // game views should be displayed
	CA_CINEMATIC        // playing a cinematic or a static pic, not connected to a server
} connstate_t;

// font support

#define GLYPH_START 0
#define GLYPH_END 255
#define GLYPH_CHARSTART 32
#define GLYPH_CHAREND 127
#define GLYPHS_PER_FONT GLYPH_END - GLYPH_START + 1
typedef struct {
	int height;     // number of scan lines
	int top;        // top of glyph in buffer
	int bottom;     // bottom of glyph in buffer
	int pitch;      // width for copying
	int xSkip;      // x adjustment
	int imageWidth; // width of actual image
	int imageHeight; // height of actual image
	float s;        // x offset in image where glyph starts
	float t;        // y offset in image where glyph starts
	float s2;
	float t2;
	qhandle_t glyph; // handle to the shader with the glyph
	char shaderName[32];
} glyphInfo_t;

typedef struct {
	glyphInfo_t glyphs[GLYPHS_PER_FONT];
	float glyphScale;
	char name[MAX_QPATH];
} fontInfo_t;

#define Square( x ) ( ( x ) * ( x ) )

// real time
//=============================================


typedef struct qtime_s {
	int tm_sec;     /* seconds after the minute - [0,59] */
	int tm_min;     /* minutes after the hour - [0,59] */
	int tm_hour;    /* hours since midnight - [0,23] */
	int tm_mday;    /* day of the month - [1,31] */
	int tm_mon;     /* months since January - [0,11] */
	int tm_year;    /* years since 1900 */
	int tm_wday;    /* days since Sunday - [0,6] */
	int tm_yday;    /* days since January 1 - [0,365] */
	int tm_isdst;   /* daylight savings time flag */
} qtime_t;


// server browser sources
#define AS_LOCAL            0
#define AS_MPLAYER      1
#define AS_GLOBAL           2
#define AS_FAVORITES    3


// cinematic states
typedef enum {
	FMV_IDLE,
	FMV_PLAY,       // play
	FMV_EOF,        // all other conditions, i.e. stop/EOF/abort
	FMV_ID_BLT,
	FMV_ID_IDLE,
	FMV_LOOPED,
	FMV_ID_WAIT
} e_status;

typedef enum _flag_status {
	FLAG_ATBASE = 0,
	FLAG_TAKEN,         // CTF
	FLAG_TAKEN_RED,     // One Flag CTF
	FLAG_TAKEN_BLUE,    // One Flag CTF
	FLAG_DROPPED
} flagStatus_t;



#define MAX_GLOBAL_SERVERS          2048
#define MAX_OTHER_SERVERS           128
#define MAX_PINGREQUESTS            16
#define MAX_SERVERSTATUSREQUESTS    16

#define SAY_ALL     0
#define SAY_TEAM    1
#define SAY_TELL    2

#define CDKEY_LEN 16
#define CDCHKSUM_LEN 2

// NERVE - SMF - localization
typedef enum {
	LANGUAGE_FRENCH = 0,
	LANGUAGE_GERMAN,
	LANGUAGE_ITALIAN,
	LANGUAGE_SPANISH,
	MAX_LANGUAGES
} languages_t;

typedef struct {
	entityState_t s;                // communicated by server to clients

	qboolean linked;                // qfalse if not in any good cluster
	int linkcount;

	int svFlags;                    // SVF_NOCLIENT, SVF_BROADCAST, etc
	int singleClient;               // only send to this client when SVF_SINGLECLIENT is set

	qboolean bmodel;                // if false, assume an explicit mins / maxs bounding box
									// only set by trap_SetBrushModel
	vec3_t mins, maxs;
	int contents;                   // CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
									// a non-solid entity should set to 0

	vec3_t absmin, absmax;          // derived from mins/maxs and origin + rotation

	// currentOrigin will be used for all collision detection and world linking.
	// it will not necessarily be the same as the trajectory evaluation for the current
	// time, because each entity must be moved one at a time after time is advanced
	// to avoid simultanious collision issues
	vec3_t currentOrigin;
	vec3_t currentAngles;

	// when a trace call is made and passEntityNum != ENTITYNUM_NONE,
	// an ent will be excluded from testing if:
	// ent->s.number == passEntityNum	(don't interact with self)
	// ent->s.ownerNum = passEntityNum	(don't interact with your own missiles)
	// entity[ent->s.ownerNum].ownerNum = passEntityNum	(don't interact with other missiles from owner)
	int ownerNum;
	int eventTime;
} entityShared_t;



// the server looks at a sharedEntity, which is the start of the game's gentity_t structure
typedef struct {
	entityState_t s;                // communicated by server to clients
	entityShared_t r;               // shared by both the server system and game
} sharedEntity_t;

#define RETRANSMIT_TIMEOUT  3000    // time between connection packet retransmits

#define LIMBOCHAT_WIDTH     140     // NERVE - SMF
#define LIMBOCHAT_HEIGHT    7       // NERVE - SMF

// snapshots are a view of the server at a given time
typedef struct {
	qboolean valid;                 // cleared if delta parsing was invalid
	int snapFlags;                  // rate delayed and dropped commands

	int serverTime;                 // server time the message is valid for (in msec)

	int messageNum;                 // copied from netchan->incoming_sequence
	int deltaNum;                   // messageNum the delta is from
	int ping;                       // time from when cmdNum-1 was sent to time packet was reeceived
	byte areamask[MAX_MAP_AREA_BYTES];                  // portalarea visibility bits

	int cmdNum;                     // the next cmdNum the server is expecting
	playerState_t ps;                       // complete information about the current player at this time

	int numEntities;                        // all of the entities that need to be presented
	int parseEntitiesNum;                   // at the time of this snapshot

	int serverCommandNum;                   // execute all commands up to this before
											// making the snapshot current
} clSnapshot_t;

typedef enum {
	AXIS_SIDE,
	AXIS_FORWARD,
	AXIS_UP,
	AXIS_ROLL,
	AXIS_YAW,
	AXIS_PITCH,
	MAX_JOYSTICK_AXIS
} joystickAxis_t;


/*
=============================================================================

the clientActive_t structure is wiped completely at every
new gamestate_t, potentially several times during an established connection

=============================================================================
*/

typedef struct {
	int p_cmdNumber;            // cl.cmdNumber when packet was sent
	int p_serverTime;           // usercmd->serverTime when packet was sent
	int p_realtime;             // cls.realtime when packet was sent
} outPacket_t;

// the parseEntities array must be large enough to hold PACKET_BACKUP frames of
// entities, so that when a delta compressed message arives from the server
// it can be un-deltad from the original
#define MAX_PARSE_ENTITIES  2048

extern int g_console_field_width;

typedef struct {
	int timeoutcount;               // it requres several frames in a timeout condition
									// to disconnect, preventing debugging breaks from
									// causing immediate disconnects on continue
	clSnapshot_t snap;              // latest received from server

	int serverTime;                 // may be paused during play
	int oldServerTime;              // to prevent time from flowing bakcwards
	int oldFrameServerTime;         // to check tournament restarts
	int serverTimeDelta;            // cl.serverTime = cls.realtime + cl.serverTimeDelta
									// this value changes as net lag varies
	qboolean extrapolatedSnapshot;      // set if any cgame frame has been forced to extrapolate
	// cleared when CL_AdjustTimeDelta looks at it
	qboolean newSnapshots;          // set on parse of any valid packet

	gameState_t gameState;          // configstrings
	char mapname[MAX_QPATH];        // extracted from CS_SERVERINFO

	int parseEntitiesNum;           // index (not anded off) into cl_parse_entities[]

	int mouseDx[2], mouseDy[2];         // added to by mouse events
	int mouseIndex;
	int joystickAxis[MAX_JOYSTICK_AXIS];            // set by joystick events

	// cgame communicates a few values to the client system
	int cgameUserCmdValue;              // current weapon to add to usercmd_t
	int cgameUserHoldableValue;         // current holdable item to add to usercmd_t	//----(SA)	added
	float cgameSensitivity;
	int cgameCld;                       // NERVE - SMF

	// cmds[cmdNumber] is the predicted command, [cmdNumber-1] is the last
	// properly generated command
	usercmd_t cmds[64];				// each mesage will send several old cmds
	int cmdNumber;                  // incremented each frame, because multiple
									// frames may need to be packed into a single packet

	outPacket_t outPackets[32];  // information about each packet we have sent out

	// the client maintains its own idea of view angles, which are
	// sent to the server each frame.  It is cleared to 0 upon entering each level.
	// the server sends a delta each frame which is added to the locally
	// tracked view angles to account for standing on rotating objects,
	// and teleport direction changes
	vec3_t viewangles;

	int serverId;                   // included in each client message so the server
									// can tell if it is for a prior map_restart
	// big stuff at end of structure so most offsets are 15 bits or less
	clSnapshot_t snapshots[32];

	entityState_t entityBaselines[MAX_GENTITIES];   // for delta compression when not in previous frame

	entityState_t parseEntities[MAX_PARSE_ENTITIES];

	// NERVE - SMF
	char limboChatMsgs[LIMBOCHAT_HEIGHT][LIMBOCHAT_WIDTH * 3 + 1];
	int limboChatPos;
	// -NERVE - SMF

	qboolean cameraMode;    //----(SA)	added for control of input while watching cinematics

} clientActive_t;

/*
=============================================================================

the clientConnection_t structure is wiped when disconnecting from a server,
either to go to a full screen console, play a demo, or connect to a different server

A connection can be to either a server through the network layer or a
demo through a file.

=============================================================================
*/


#define DO_NET_ENCODE 0

#define PACKET_BACKUP   32  // number of old messages that must be kept on client and
// server for delta comrpession and ping estimation
#define PACKET_MASK     ( PACKET_BACKUP - 1 )

#define MAX_PACKET_USERCMDS     32      // max number of usercmd_t in a packet

#define PORT_ANY            -1

// RF, increased this, seems to keep causing problems when set to 64, especially when loading
// a savegame, which is hard to fix on that side, since we can't really spread out a loadgame
// among several frames
//#define	MAX_RELIABLE_COMMANDS	64			// max string commands buffered for restransmit
//#define	MAX_RELIABLE_COMMANDS	128			// max string commands buffered for restransmit
#define MAX_RELIABLE_COMMANDS   256 // bigger!

typedef enum {
	NA_BOT,
	NA_BAD,                 // an address lookup failed
	NA_LOOPBACK,
	NA_BROADCAST,
	NA_IP,
	NA_IPX,
	NA_BROADCAST_IPX
} netadrtype_t;

typedef enum {
	NS_CLIENT,
	NS_SERVER
} netsrc_t;

typedef struct {
	netadrtype_t type;

	byte ip[4];
	byte ipx[10];

	unsigned short port;
} netadr_t;

#define MAX_MSGLEN              32768       // max length of a message, which may

#define MAX_DOWNLOAD_WINDOW         8       // max of eight download frames
#define MAX_DOWNLOAD_BLKSIZE        2048    // 2048 byte block chunks

typedef struct {
	netsrc_t sock;

	int dropped;                    // between last packet and previous

	netadr_t remoteAddress;
	int qport;                      // qport value to write when transmitting

	// sequencing variables
	int incomingSequence;
	int outgoingSequence;

	// incoming fragment assembly buffer
	int fragmentSequence;
	int fragmentLength;
	byte fragmentBuffer[MAX_MSGLEN];

	// outgoing fragment buffer
	// we need to space out the sending of large fragmented messages
	qboolean unsentFragments;
	int unsentFragmentStart;
	int unsentLength;
	byte unsentBuffer[MAX_MSGLEN];
} netchan_t;

typedef struct {

	int clientNum;
	int lastPacketSentTime;                 // for retransmits during connection
	int lastPacketTime;                     // for timeouts

	netadr_t serverAddress;
	int connectTime;                        // for connection retransmits
	int connectPacketCount;                 // for display on connection dialog
	char serverMessage[MAX_STRING_TOKENS];          // for display on connection dialog

	int challenge;                          // from the server to use for connecting
	int checksumFeed;                       // from the server for checksum calculations

	// these are our reliable messages that go to the server
	int reliableSequence;
	int reliableAcknowledge;                // the last one the server has executed
	char reliableCommands[256][MAX_TOKEN_CHARS];

	// server message (unreliable) and command (reliable) sequence
	// numbers are NOT cleared at level changes, but continue to
	// increase as long as the connection is valid

	// message sequence is used by both the network layer and the
	// delta compression layer
	int serverMessageSequence;

	// reliable messages received from server
	int serverCommandSequence;
	int lastExecutedServerCommand;              // last server command grabbed or executed with CL_GetServerCommand
	char serverCommands[256][MAX_TOKEN_CHARS];

	// file transfer from server
	fileHandle_t download;
	char downloadTempName[MAX_OSPATH];
	char downloadName[MAX_OSPATH];
	int downloadNumber;
	int downloadBlock;          // block we are waiting for
	int downloadCount;          // how many bytes we got
	int downloadSize;           // how many bytes we got
	char downloadList[MAX_INFO_STRING];        // list of paks we need to download
	qboolean downloadRestart;       // if true, we need to do another FS_Restart because we downloaded a pak

	// demo information
	char demoName[MAX_QPATH];
	qboolean demorecording;
	qboolean demoplaying;
	qboolean demowaiting;       // don't record until a non-delta message is received
	qboolean firstDemoFrameSkipped;
	fileHandle_t demofile;

	int timeDemoFrames;             // counter of rendered frames
	int timeDemoStart;              // cls.realtime before first frame
	int timeDemoBaseTime;           // each frame will be at this time + frameNum * 50

	// big stuff at end of structure so most offsets are 15 bits or less
	netchan_t netchan;
} clientConnection_t;

#define MAX_CORONAS     32          //----(SA)	not really a reason to limit this other than trying to keep a reasonable count
#define MAX_DLIGHTS     32          // can't be increased, because bit flags are used on surfaces
#define MAX_ENTITIES    1023        // can't be increased without changing drawsurf bit packing

// renderfx flags
#define RF_MINLIGHT         1       // allways have some light (viewmodel, some items)
#define RF_THIRD_PERSON     2       // don't draw through eyes, only mirrors (player bodies, chat sprites)
#define RF_FIRST_PERSON     4       // only draw through eyes (view weapon, damage blood blob)
#define RF_DEPTHHACK        8       // for view weapon Z crunching
#define RF_NOSHADOW         64      // don't add stencil shadows

#define RF_LIGHTING_ORIGIN  128     // use refEntity->lightingOrigin instead of refEntity->origin
									// for lighting.  This allows entities to sink into the floor
									// with their origin going solid, and allows all parts of a
									// player to get the same lighting
#define RF_SHADOW_PLANE     256     // use refEntity->shadowPlane
#define RF_WRAP_FRAMES      512     // mod the model frames by the maxframes to allow continuous
									// animation without needing to know the frame count

#define RF_HILIGHT          ( 1 << 8 )  // more than RF_MINLIGHT.  For when an object is "Highlighted" (looked at/training identification/etc)
#define RF_BLINK            ( 1 << 9 )  // eyes in 'blink' state

// refdef flags
#define RDF_NOWORLDMODEL    1       // used for player configuration screen
#define RDF_HYPERSPACE      4       // teleportation effect

// Rafael
#define RDF_SKYBOXPORTAL    8

#define RDF_DRAWSKYBOX      16      // the above marks a scene as being a 'portal sky'.  this flag says to draw it or not

//----(SA)
#define RDF_UNDERWATER      ( 1 << 4 )  // so the renderer knows to use underwater fog when the player is underwater
#define RDF_DRAWINGSKY      ( 1 << 5 )
#define RDF_SNOOPERVIEW     ( 1 << 6 )  //----(SA)	added


typedef struct {
	vec3_t xyz;
	float st[2];
	byte modulate[4];
} polyVert_t;

typedef struct poly_s {
	qhandle_t hShader;
	int numVerts;
	polyVert_t          *verts;
} poly_t;

typedef enum {
	RT_MODEL,
	RT_POLY,
	RT_SPRITE,
	RT_SPLASH,  // ripple effect
	RT_BEAM,
	RT_RAIL_CORE,
	RT_RAIL_CORE_TAPER, // a modified core that creates a properly texture mapped core that's wider at one end
	RT_RAIL_RINGS,
	RT_LIGHTNING,
	RT_PORTALSURFACE,       // doesn't draw anything, just info for portals

	RT_MAX_REF_ENTITY_TYPE
} refEntityType_t;

#define ZOMBIEFX_FADEOUT_TIME   10000

#define REFLAG_ONLYHAND     1   // only draw hand surfaces
#define REFLAG_ZOMBIEFX     2   // special post-tesselation processing for zombie skin
#define REFLAG_ZOMBIEFX2    4   // special post-tesselation processing for zombie skin
#define REFLAG_FORCE_LOD    8   // force a low lod
#define REFLAG_ORIENT_LOD   16  // on LOD switch, align the model to the player's camera
#define REFLAG_DEAD_LOD     32  // allow the LOD to go lower than recommended
#define REFLAG_SCALEDSPHERECULL 64  // on LOD switch, align the model to the player's camera
#define REFLAG_FULL_LOD     8   // force a FULL lod

typedef struct {
	refEntityType_t reType;
	int renderfx;

	qhandle_t hModel;               // opaque type outside refresh

	// most recent data
	vec3_t lightingOrigin;          // so multi-part models can be lit identically (RF_LIGHTING_ORIGIN)
	float shadowPlane;              // projection shadows go here, stencils go slightly lower

	vec3_t axis[3];                 // rotation vectors
	vec3_t torsoAxis[3];            // rotation vectors for torso section of skeletal animation
	qboolean nonNormalizedAxes;     // axis are not normalized, i.e. they have scale
	float origin[3];                // also used as MODEL_BEAM's "from"
	int frame;                      // also used as MODEL_BEAM's diameter
	int torsoFrame;                 // skeletal torso can have frame independant of legs frame

	vec3_t scale;       //----(SA)	added

	// previous data for frame interpolation
	float oldorigin[3];             // also used as MODEL_BEAM's "to"
	int oldframe;
	int oldTorsoFrame;
	float backlerp;                 // 0.0 = current, 1.0 = old
	float torsoBacklerp;

	// texturing
	int skinNum;                    // inline skin index
	qhandle_t customSkin;           // NULL for default skin
	qhandle_t customShader;         // use one image for the entire thing

	// misc
	byte shaderRGBA[4];             // colors used by rgbgen entity shaders
	float shaderTexCoord[2];        // texture coordinates used by tcMod entity modifiers
	float shaderTime;               // subtracted from refdef time to control effect start times

	// extra sprite information
	float radius;
	float rotation;

	// Ridah
	vec3_t fireRiseDir;

	// Ridah, entity fading (gibs, debris, etc)
	int fadeStartTime, fadeEndTime;

	float hilightIntensity;         //----(SA)	added

	int reFlags;

	int entityNum;                  // currentState.number, so we can attach rendering effects to specific entities (Zombie)

} refEntity_t;

//----(SA)

//                                                                  //
// WARNING:: synch FOG_SERVER in sv_ccmds.c if you change anything	//
//                                                                  //
typedef enum {
	FOG_NONE,       //	0

	FOG_SKY,        //	1	fog values to apply to the sky when using density fog for the world (non-distance clipping fog) (only used if(glfogsettings[FOG_MAP].registered) or if(glfogsettings[FOG_MAP].registered))
	FOG_PORTALVIEW, //	2	used by the portal sky scene
	FOG_HUD,        //	3	used by the 3D hud scene

	//		The result of these for a given frame is copied to the scene.glFog when the scene is rendered

	// the following are fogs applied to the main world scene
	FOG_MAP,        //	4	use fog parameter specified using the "fogvars" in the sky shader
	FOG_WATER,      //	5	used when underwater
	FOG_SERVER,     //	6	the server has set my fog (probably a target_fog) (keep synch in sv_ccmds.c !!!)
	FOG_CURRENT,    //	7	stores the current values when a transition starts
	FOG_LAST,       //	8	stores the current values when a transition starts
	FOG_TARGET,     //	9	the values it's transitioning to.

	FOG_CMD_SWITCHFOG,  // 10	transition to the fog specified in the second parameter of R_SetFog(...) (keep synch in sv_ccmds.c !!!)

	NUM_FOGS
} glfogType_t;


typedef struct {
	int mode;                   // GL_LINEAR, GL_EXP
	int hint;                   // GL_DONT_CARE
	int startTime;              // in ms
	int finishTime;             // in ms
	float color[4];
	float start;                // near
	float end;                  // far
	qboolean useEndForClip;     // use the 'far' value for the far clipping plane
	float density;              // 0.0-1.0
	qboolean registered;        // has this fog been set up?
	qboolean drawsky;           // draw skybox
	qboolean clearscreen;       // clear the GL color buffer

	int dirty;
} glfog_t;

//----(SA)	end


#define MAX_RENDER_STRINGS          8
#define MAX_RENDER_STRING_LENGTH    32

typedef struct {
	int x, y, width, height;
	float fov_x, fov_y;
	vec3_t vieworg;
	vec3_t viewaxis[3];             // transformation matrix

	int time;           // time in milliseconds for shader effects and other time dependent rendering issues
	int rdflags;                    // RDF_NOWORLDMODEL, etc

	// 1 bits will prevent the associated area from rendering at all
	byte areamask[MAX_MAP_AREA_BYTES];




	// text messages for deform text shaders
	char text[MAX_RENDER_STRINGS][MAX_RENDER_STRING_LENGTH];


	//----(SA)	added (needed to pass fog infos into the portal sky scene)
	glfog_t glfog;
	//----(SA)	end

} refdef_t;


typedef enum {
	STEREO_CENTER,
	STEREO_LEFT,
	STEREO_RIGHT
} stereoFrame_t;


/*
** glconfig_t
**
** Contains variables specific to the OpenGL configuration
** being run right now.  These are constant once the OpenGL
** subsystem is initialized.
*/
typedef enum {
	TC_NONE,
	TC_S3TC,
	TC_EXT_COMP_S3TC
} textureCompression_t;

typedef enum {
	GLDRV_ICD,                  // driver is integrated with window system
								// WARNING: there are tests that check for
								// > GLDRV_ICD for minidriverness, so this
								// should always be the lowest value in this
								// enum set
								GLDRV_STANDALONE,           // driver is a non-3Dfx standalone driver
								GLDRV_VOODOO                // driver is a 3Dfx standalone driver
} glDriverType_t;

typedef enum {
	GLHW_GENERIC,           // where everthing works the way it should
	GLHW_3DFX_2D3D,         // Voodoo Banshee or Voodoo3, relevant since if this is
							// the hardware type then there can NOT exist a secondary
							// display adapter
							GLHW_RIVA128,           // where you can't interpolate alpha
							GLHW_RAGEPRO,           // where you can't modulate alpha on alpha textures
							GLHW_PERMEDIA2          // where you don't have src*dst
} glHardwareType_t;

typedef struct {
	char renderer_string[MAX_STRING_CHARS];
	char vendor_string[MAX_STRING_CHARS];
	char version_string[MAX_STRING_CHARS];
	char extensions_string[4 * MAX_STRING_CHARS];                       // this is actually too short for many current cards/drivers  // (SA) doubled from 2x to 4x MAX_STRING_CHARS

	int maxTextureSize;                             // queried from GL
	int maxActiveTextures;                          // multitexture ability

	int colorBits, depthBits, stencilBits;

	glDriverType_t driverType;
	glHardwareType_t hardwareType;

	qboolean deviceSupportsGamma;
	textureCompression_t textureCompression;
	qboolean textureEnvAddAvailable;
	qboolean anisotropicAvailable;                  //----(SA)	added
	float maxAnisotropy;                            //----(SA)	added

	// vendor-specific support
	// NVidia
	qboolean NVFogAvailable;                    //----(SA)	added
	int NVFogMode;                                  //----(SA)	added
	// ATI
	int ATIMaxTruformTess;                          // for truform support
	int ATINormalMode;                          // for truform support
	int ATIPointMode;                           // for truform support


	int vidWidth, vidHeight;
	// aspect is the screen's physical width / height, which may be different
	// than scrWidth / scrHeight if the pixels are non-square
	// normal screens should be 4/3, but wide aspect monitors may be 16/9
	float windowAspect;

	int displayFrequency;

	// synonymous with "does rendering consume the entire screen?", therefore
	// a Voodoo or Voodoo2 will have this set to TRUE, as will a Win32 ICD that
	// used CDS.
	qboolean isFullscreen;
	qboolean stereoEnabled;
	qboolean smpActive;                     // dual processor

	qboolean textureFilterAnisotropicAvailable;                 //DAJ
} glconfig_t;



/*
==================================================================

the clientStatic_t structure is never wiped, and is used even when
no client connection is active at all

==================================================================
*/

typedef struct {
	netadr_t adr;
	int start;
	int time;
	char info[MAX_INFO_STRING];
} ping_t;

typedef struct {
	netadr_t adr;
	char hostName[MAX_NAME_LENGTH];
	char mapName[MAX_NAME_LENGTH];
	char game[MAX_NAME_LENGTH];
	int netType;
	int gameType;
	int clients;
	int maxClients;
	int minPing;
	int maxPing;
	int ping;
	qboolean visible;
	int allowAnonymous;
} serverInfo_t;

typedef struct {
	byte ip[4];
	unsigned short port;
} serverAddress_t;

typedef struct {
	connstate_t state;              // connection status
	int keyCatchers;                // bit flags

	qboolean cddialog;              // bring up the cd needed dialog next frame
	qboolean endgamemenu;           // bring up the end game credits menu next frame

	char servername[MAX_OSPATH];            // name of server from original connect (used by reconnect)

	// when the server clears the hunk, all of these must be restarted
	qboolean rendererStarted;
	qboolean soundStarted;
	qboolean soundRegistered;
	qboolean uiStarted;
	qboolean cgameStarted;

	int framecount;
	int frametime;                  // msec since last frame

	int realtime;                   // ignores pause
	int realFrametime;              // ignoring pause, so console always works

	int numlocalservers;
	serverInfo_t localServers[MAX_OTHER_SERVERS];

	int numglobalservers;
	serverInfo_t globalServers[MAX_GLOBAL_SERVERS];
	// additional global servers
	int numGlobalServerAddresses;
	serverAddress_t globalServerAddresses[MAX_GLOBAL_SERVERS];

	int numfavoriteservers;
	serverInfo_t favoriteServers[MAX_OTHER_SERVERS];

	int nummplayerservers;
	serverInfo_t mplayerServers[MAX_OTHER_SERVERS];

	int pingUpdateSource;       // source currently pinging or updating

	int masterNum;

	// update server info
	netadr_t updateServer;
	char updateChallenge[MAX_TOKEN_CHARS];
	char updateInfoString[MAX_INFO_STRING];

	netadr_t authorizeServer;

	// rendering info
	glconfig_t glconfig;
	qhandle_t charSetShader;
	qhandle_t whiteShader;
	qhandle_t consoleShader;
	qhandle_t consoleShader2;   //----(SA)	added

} clientStatic_t;

typedef struct {
	int down[2];                // key nums holding it down
	unsigned downtime;          // msec timestamp
	unsigned msec;              // msec down this frame if both a down and up happened
	qboolean active;            // current state
	qboolean wasPressed;        // set when down, not cleared when up
} kbutton_t;

typedef enum {
	KB_LEFT,
	KB_RIGHT,
	KB_FORWARD,
	KB_BACK,
	KB_LOOKUP,
	KB_LOOKDOWN,
	KB_MOVELEFT,
	KB_MOVERIGHT,
	KB_STRAFE,
	KB_SPEED,
	KB_UP,
	KB_DOWN,
	KB_BUTTONS0,
	KB_BUTTONS1,
	KB_BUTTONS2,
	KB_BUTTONS3,
	KB_BUTTONS4,
	KB_BUTTONS5,
	KB_BUTTONS6,
	KB_BUTTONS7,
	KB_WBUTTONS0,
	KB_WBUTTONS1,
	KB_WBUTTONS2,
	KB_WBUTTONS3,
	KB_WBUTTONS4,
	KB_WBUTTONS5,
	KB_WBUTTONS6,
	KB_WBUTTONS7,
	KB_MLOOK,
	KB_KICK,

	NUM_BUTTONS
} kbuttons_t;

typedef enum {
	PM_NORMAL,      // can accelerate and turn
	PM_NOCLIP,      // noclip movement
	PM_SPECTATOR,   // still run into walls
	PM_DEAD,        // no acceleration or turning, but free falling
	PM_FREEZE,      // stuck in place with no control
	PM_INTERMISSION // no movement or status bar
} pmtype_t;

typedef enum {
	WEAPON_READY,
	WEAPON_RAISING,
	WEAPON_RAISING_TORELOAD,    //----(SA)	added
	WEAPON_DROPPING,
	WEAPON_DROPPING_TORELOAD,   //----(SA)	added.  will reload upon completion of weapon switch
	WEAPON_READYING,    // getting from 'ready' to 'firing'
	WEAPON_RELAXING,    // weapon is ready, but since not firing, it's on it's way to a "relaxed" stance
	WEAPON_VENOM_REST,
	WEAPON_FIRING,
	WEAPON_FIRINGALT,
	WEAPON_WAITING,     //----(SA)	added.  player allowed to switch/reload, but not fire
	WEAPON_RELOADING    //----(SA)	added
} weaponstate_t;

// pmove->pm_flags	(sent as max 16 bits in msg.c)
#define PMF_DUCKED          1
#define PMF_JUMP_HELD       2
#define PMF_LADDER          4       // player is on a ladder
#define PMF_BACKWARDS_JUMP  8       // go into backwards land
#define PMF_BACKWARDS_RUN   16      // coast down to backwards run
#define PMF_TIME_LAND       32      // pm_time is time before rejump
#define PMF_TIME_KNOCKBACK  64      // pm_time is an air-accelerate only time
#define PMF_TIME_WATERJUMP  256     // pm_time is waterjump
#define PMF_RESPAWNED       512     // clear after attack and jump buttons come up
#define PMF_USE_ITEM_HELD   1024
// RF, removed since it's not used
//#define PMF_GRAPPLE_PULL	2048	// pull towards grapple location
#define PMF_IGNORE_INPUT    2048    // no movement/firing commands allowed
#define PMF_FOLLOW          4096    // spectate following another player
#define PMF_SCOREBOARD      8192    // spectate as a scoreboard
#define PMF_LIMBO           16384   // JPW NERVE limbo state, pm_time is time until reinforce
#define PMF_TIME_LOAD       32768   // hold for this time after a load game, and prevent large thinks

#define PMF_ALL_TIMES   ( PMF_TIME_WATERJUMP | PMF_TIME_LAND | PMF_TIME_KNOCKBACK | PMF_TIME_LOAD )

#define MAXTOUCH    32
typedef struct {
	// state (in / out)
	playerState_t   *ps;

	// command (in)
	usercmd_t cmd, oldcmd;
	int tracemask;                  // collide against these types of surfaces
	int debugLevel;                 // if set, diagnostic output will be printed
	qboolean noFootsteps;           // if the game is setup for no footsteps by the server
	qboolean noWeapClips;               // if the game is setup for no weapon clips by the server
	qboolean gauntletHit;           // true if a gauntlet attack would actually hit something

	// results (out)
	int numtouch;
	int touchents[MAXTOUCH];

	vec3_t mins, maxs;              // bounding box size

	int watertype;
	int waterlevel;

	float xyspeed;

	// for fixed msec Pmove
	int pmove_fixed;
	int pmove_msec;

	// callbacks to test the world
	// these will be different functions during game and cgame
	void(*trace)(trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentMask);
	int(*pointcontents)(const vec3_t point, int passEntityNum);
} pmove_t;

// contents flags are seperate bits
// a given brush can contribute multiple content bits

// these definitions also need to be in q_shared.h!

#define CONTENTS_SOLID          1       // an eye is never valid in a solid

#define CONTENTS_LIGHTGRID      4   //----(SA)	added

#define CONTENTS_LAVA           8
#define CONTENTS_SLIME          16
#define CONTENTS_WATER          32
#define CONTENTS_FOG            64


//----(SA) added
#define CONTENTS_MISSILECLIP    128 // 0x80
#define CONTENTS_ITEM           256 // 0x100
//----(SA) end

// RF, AI sight/nosight & bullet/nobullet
#define CONTENTS_AI_NOSIGHT     0x1000  // AI cannot see through this
#define CONTENTS_CLIPSHOT       0x2000  // bullets hit this
// RF, end

#define CONTENTS_MOVER          0x4000
#define CONTENTS_AREAPORTAL     0x8000

#define CONTENTS_PLAYERCLIP     0x10000
#define CONTENTS_MONSTERCLIP    0x20000

//bot specific contents types
#define CONTENTS_TELEPORTER     0x40000
#define CONTENTS_JUMPPAD        0x80000
#define CONTENTS_CLUSTERPORTAL  0x100000
#define CONTENTS_DONOTENTER     0x200000
#define CONTENTS_DONOTENTER_LARGE       0x400000

#define CONTENTS_ORIGIN         0x1000000   // removed before bsping an entity

#define CONTENTS_BODY           0x2000000   // should never be on a brush, only in game
#define CONTENTS_CORPSE         0x4000000
#define CONTENTS_DETAIL         0x8000000   // brushes not used for the bsp

#define CONTENTS_STRUCTURAL     0x10000000  // brushes used for the bsp
#define CONTENTS_TRANSLUCENT    0x20000000  // don't consume surface fragments inside
#define CONTENTS_TRIGGER        0x40000000
#define CONTENTS_NODROP         0x80000000  // don't leave bodies or items (death fog, lava)zz

#define SURF_NODAMAGE           0x1     // never give falling damage
#define SURF_SLICK              0x2     // effects game physics
#define SURF_SKY                0x4     // lighting from environment map
#define SURF_LADDER             0x8
#define SURF_NOIMPACT           0x10    // don't make missile explosions
#define SURF_NOMARKS            0x20    // don't leave missile marks
//#define	SURF_FLESH			0x40	// make flesh sounds and effects
#define SURF_CERAMIC            0x40    // out of surf's, so replacing unused 'SURF_FLESH'
#define SURF_NODRAW             0x80    // don't generate a drawsurface at all
#define SURF_HINT               0x100   // make a primary bsp splitter
#define SURF_SKIP               0x200   // completely ignore, allowing non-closed brushes
#define SURF_NOLIGHTMAP         0x400   // surface doesn't need a lightmap
#define SURF_POINTLIGHT         0x800   // generate lighting info at vertexes
// JOSEPH 9-16-99
#define SURF_METAL              0x1000  // clanking footsteps
// END JOSEPH
#define SURF_NOSTEPS            0x2000  // no footstep sounds
#define SURF_NONSOLID           0x4000  // don't collide against curves with this set
#define SURF_LIGHTFILTER        0x8000  // act as a light filter during q3map -light
#define SURF_ALPHASHADOW        0x10000 // do per-pixel light shadow casting in q3map
#define SURF_NODLIGHT           0x20000 // don't dlight even if solid (solid lava, skies)
// JOSEPH 9-16-99
// Ridah, 11-01-99 (Q3 merge)
#define SURF_WOOD               0x40000
#define SURF_GRASS              0x80000
#define SURF_GRAVEL             0x100000
// END JOSEPH

// (SA)
//#define SURF_SMGROUP			0x200000
#define SURF_GLASS              0x200000    // out of surf's, so replacing unused 'SURF_SMGROUP'
#define SURF_SNOW               0x400000
#define SURF_ROOF               0x800000

//#define	SURF_RUBBLE				0x1000000	// stole 'rubble' for
#define SURF_RUBBLE             0x1000000
#define SURF_CARPET             0x2000000

#define SURF_MONSTERSLICK       0x4000000   // slick surf that only affects ai's
// #define SURF_DUST				0x8000000 // leave a dust trail when walking on this surface
#define SURF_MONSLICK_W         0x8000000

#define SURF_MONSLICK_N         0x10000000
#define SURF_MONSLICK_E         0x20000000
#define SURF_MONSLICK_S         0x40000000



// entityState_t->eFlags
#define EF_DEAD             0x00000001      // don't draw a foe marker over players with EF_DEAD
#define EF_NONSOLID_BMODEL  0x00000002      // bmodel is visible, but not solid
#define EF_FORCE_END_FRAME  EF_NONSOLID_BMODEL  // force client to end of current animation (after loading a savegame)
#define EF_TELEPORT_BIT     0x00000004      // toggled every time the origin abruptly changes
#define EF_MONSTER_EFFECT   0x00000008      // draw an aiChar dependant effect for this character
#define EF_CAPSULE          0x00000010      // use capsule for collisions
#define EF_CROUCHING        0x00000020      // player is crouching
#define EF_MG42_ACTIVE      0x00000040      // currently using an MG42
#define EF_NODRAW           0x00000080      // may have an event, but no model (unspawned items)
#define EF_FIRING           0x00000100      // for lightning gun
#define EF_INHERITSHADER    EF_FIRING       // some ents will never use EF_FIRING, hijack it for "USESHADER"
#define EF_BOUNCE_HEAVY     0x00000200      // more realistic bounce.  not as rubbery as above (currently for c4)
#define EF_SPINNING         0x00000400      // (SA) added for level editor control of spinning pickup items
#define EF_BREATH           EF_SPINNING     // Characters will not have EF_SPINNING set, hijack for drawing character breath

#define EF_MELEE_ACTIVE     0x00000800      // (SA) added for client knowledge of melee items held (chair/etc.)
#define EF_TALK             0x00001000      // draw a talk balloon
#define EF_CONNECTION       0x00002000      // draw a connection trouble sprite
#define EF_MONSTER_EFFECT2  0x00004000      // show the secondary special effect for this character
#define EF_HEADSHOT         0x00008000      // last hit to player was head shot
#define EF_MONSTER_EFFECT3  0x00010000      // show the third special effect for this character
#define EF_HEADLOOK         0x00020000      // make the head look around
#define EF_STAND_IDLE2      0x00040000      // when standing, play idle2 instead of the default
#define EF_VIEWING_CAMERA   EF_STAND_IDLE2  // NOTE: REMOVE STAND_IDLE2 !!
#define EF_TAGCONNECT       0x00080000      // connected to another entity via tag
// RF, disabled, not used anymore
//#define EF_MOVER_BLOCKED	0x00100000		// mover was blocked dont lerp on the client
#define EF_NO_TURN_ANIM     0x00100000      // dont play turning anims in the cgame
#define EF_FORCED_ANGLES    0x00200000  // enforce all body parts to use these angles

#define EF_ZOOMING          0x00400000      // client is zooming
#define EF_NOSWINGANGLES    0x00800000      // try and keep all parts facing same direction

#define EF_DUMMY_PMOVE      0x01000000
#define EF_VOTED            0x02000000      // already cast a vote
#define EF_BOUNCE           0x04000000      // for missiles
#define EF_CIG              EF_BOUNCE       // players should never use bounce, hijack for cigarette
#define EF_BOUNCE_HALF      0x08000000      // for missiles
#define EF_MOVER_STOP       0x10000000      // will push otherwise	// (SA) moved down to make space for one more client flag
#define EF_MOVER_ANIMATE    0x20000000      // interpolate animation
#define EF_DEATH_FRAME      EF_MOVER_ANIMATE    // hijack to stick death at last frame after vid_restart
#define EF_RECENTLY_FIRING  0x40000000      // fired recently, lock torso angles, etc

typedef enum {
	PW_NONE,

	PW_QUAD,
	PW_BATTLESUIT,
	PW_HASTE,
	PW_INVIS,
	PW_REGEN,
	PW_FLIGHT,

	// (SA) for Wolf
	PW_INVULNERABLE,
	//	PW_FIRE,			//----(SA)
	//	PW_ELECTRIC,		//----(SA)
	//	PW_BREATHER,		//----(SA)
	PW_NOFATIGUE,       //----(SA)

	PW_REDFLAG,
	PW_BLUEFLAG,
	PW_BALL,

	PW_NUM_POWERUPS
} powerup_t;

typedef struct ammotable_s {
	int maxammo;            //
	int uses;               //
	int maxclip;            //
	int reloadTime;         //
	int fireDelayTime;      //
	int nextShotTime;       //
//----(SA)	added
	int maxHeat;            // max active firing time before weapon 'overheats' (at which point the weapon will fail)
	int coolRate;           // how fast the weapon cools down. (per second)
//----(SA)	end
	int mod;                // means of death
} ammotable_t;

typedef enum {
	EV_NONE,
	EV_FOOTSTEP,
	EV_FOOTSTEP_METAL,
	EV_FOOTSTEP_WOOD,
	EV_FOOTSTEP_GRASS,
	EV_FOOTSTEP_GRAVEL,
	EV_FOOTSTEP_ROOF,
	EV_FOOTSTEP_SNOW,
	EV_FOOTSTEP_CARPET,
	EV_FOOTSPLASH,
	EV_FOOTWADE,
	EV_SWIM,
	EV_STEP_4,
	EV_STEP_8,
	EV_STEP_12,
	EV_STEP_16,
	EV_FALL_SHORT,
	EV_FALL_MEDIUM,
	EV_FALL_FAR,
	EV_FALL_NDIE,
	EV_FALL_DMG_10,
	EV_FALL_DMG_15,
	EV_FALL_DMG_25,
	EV_FALL_DMG_50,
	EV_JUMP_PAD,            // boing sound at origin, jump sound on player
	EV_JUMP,
	EV_WATER_TOUCH, // foot touches
	EV_WATER_LEAVE, // foot leaves
	EV_WATER_UNDER, // head touches
	EV_WATER_CLEAR, // head leaves
	EV_ITEM_PICKUP,         // normal item pickups are predictable
	EV_ITEM_PICKUP_QUIET,   // (SA) same, but don't play the default pickup sound as it was specified in the ent
	EV_GLOBAL_ITEM_PICKUP,  // powerup / team sounds are broadcast to everyone
	EV_NOITEM,
	EV_NOAMMO,
	EV_EMPTYCLIP,
	EV_FILL_CLIP,
	EV_WEAP_OVERHEAT,
	EV_CHANGE_WEAPON,
	EV_FIRE_WEAPON,
	EV_FIRE_WEAPONB,
	EV_FIRE_WEAPON_LASTSHOT,
	EV_FIRE_QUICKGREN,  // "Quickgrenade"
	EV_NOFIRE_UNDERWATER,
	EV_FIRE_WEAPON_MG42,
	EV_SUGGESTWEAP,     //----(SA)	added
	EV_GRENADE_SUICIDE, //----(SA)	added
	EV_USE_ITEM0,
	EV_USE_ITEM1,
	EV_USE_ITEM2,
	EV_USE_ITEM3,
	EV_USE_ITEM4,
	EV_USE_ITEM5,
	EV_USE_ITEM6,
	EV_USE_ITEM7,
	EV_USE_ITEM8,
	EV_USE_ITEM9,
	EV_USE_ITEM10,
	EV_USE_ITEM11,
	EV_USE_ITEM12,
	EV_USE_ITEM13,
	EV_USE_ITEM14,
	EV_USE_ITEM15,
	EV_ITEM_RESPAWN,
	EV_ITEM_POP,
	EV_PLAYER_TELEPORT_IN,
	EV_PLAYER_TELEPORT_OUT,
	EV_GRENADE_BOUNCE,      // eventParm will be the soundindex
	EV_GENERAL_SOUND,
	EV_GLOBAL_SOUND,        // no attenuation
	EV_BULLET_HIT_FLESH,
	EV_BULLET_HIT_WALL,
	EV_MISSILE_HIT,
	EV_MISSILE_MISS,
	EV_RAILTRAIL,
	EV_VENOM,
	EV_VENOMFULL,
	EV_BULLET,              // otherEntity is the shooter
	EV_LOSE_HAT,            //----(SA)
	EV_GIB_HEAD,            // only blow off the head
	EV_PAIN,
	EV_CROUCH_PAIN,
	EV_DEATH1,
	EV_DEATH2,
	EV_DEATH3,
	EV_ENTDEATH,    //----(SA)	added
	EV_OBITUARY,
	EV_POWERUP_QUAD,
	EV_POWERUP_BATTLESUIT,
	EV_POWERUP_REGEN,
	EV_GIB_PLAYER,          // gib a previously living player
	EV_DEBUG_LINE,
	EV_STOPLOOPINGSOUND,
	EV_STOPSTREAMINGSOUND,
	EV_TAUNT,
	EV_SMOKE,
	EV_SPARKS,
	EV_SPARKS_ELECTRIC,
	EV_BATS,
	EV_BATS_UPDATEPOSITION,
	EV_BATS_DEATH,
	EV_EXPLODE,     // func_explosive
	EV_EFFECT,      // target_effect
	EV_MORTAREFX,   // mortar firing
	EV_SPINUP,  // JPW NERVE panzerfaust preamble
	EV_SNOW_ON,
	EV_SNOW_OFF,
	EV_MISSILE_MISS_SMALL,
	EV_MISSILE_MISS_LARGE,
	EV_WOLFKICK_HIT_FLESH,
	EV_WOLFKICK_HIT_WALL,
	EV_WOLFKICK_MISS,
	EV_SPIT_HIT,
	EV_SPIT_MISS,
	EV_SHARD,
	EV_JUNK,
	EV_EMITTER, //----(SA)	added // generic particle emitter that uses client-side particle scripts
	EV_OILPARTICLES,
	EV_OILSLICK,
	EV_OILSLICKREMOVE,
	EV_MG42EFX,
	EV_FLAMEBARREL_BOUNCE,
	EV_FLAKGUN1,
	EV_FLAKGUN2,
	EV_FLAKGUN3,
	EV_FLAKGUN4,
	EV_EXERT1,
	EV_EXERT2,
	EV_EXERT3,
	EV_SNOWFLURRY,
	EV_CONCUSSIVE,
	EV_DUST,
	EV_RUMBLE_EFX,
	EV_GUNSPARKS,
	EV_FLAMETHROWER_EFFECT,
	EV_SNIPER_SOUND,
	EV_POPUP,
	EV_POPUPBOOK,
	EV_GIVEPAGE,    //----(SA)	added
	EV_CLOSEMENU,   //----(SA)	added
	EV_SPAWN_SPIRIT,

	EV_MAX_EVENTS   // just added as an 'endcap'

} entity_event_t;

typedef struct gentity_s gentity_t;
typedef struct gclient_s gclient_t;

//====================================================================
//
// Scripting, these structure are not saved into savegames (parsed each start)
typedef struct
{
	char    *actionString;
	qboolean(*actionFunc)(gentity_t *ent, char *params);
} g_script_stack_action_t;
//
typedef struct
{
	//
	// set during script parsing
	g_script_stack_action_t     *action;            // points to an action to perform
	char                        *params;
} g_script_stack_item_t;
//
#define G_MAX_SCRIPT_STACK_ITEMS    64
//
typedef struct
{
	g_script_stack_item_t items[G_MAX_SCRIPT_STACK_ITEMS];
	int numItems;
} g_script_stack_t;
//
typedef struct
{
	int eventNum;                           // index in scriptEvents[]
	char                *params;            // trigger targetname, etc
	g_script_stack_t stack;
} g_script_event_t;
//
typedef struct
{
	char        *eventStr;
	qboolean(*eventMatch)(g_script_event_t *event, char *eventParm);
} g_script_event_define_t;

typedef struct
{
	int scriptStackHead, scriptStackChangeTime;
	int scriptEventIndex;       // current event containing stack of actions to perform
	// scripting system variables
	int scriptId;                   // incremented each time the script changes
	int scriptFlags;
	char    *animatingParams;
} g_script_status_t;
//
#define G_MAX_SCRIPT_ACCUM_BUFFERS  8

typedef enum {
	MOVER_POS1,
	MOVER_POS2,
	MOVER_POS3,
	MOVER_1TO2,
	MOVER_2TO1,
	// JOSEPH 1-26-00
	MOVER_2TO3,
	MOVER_3TO2,
	// END JOSEPH

	// Rafael
	MOVER_POS1ROTATE,
	MOVER_POS2ROTATE,
	MOVER_1TO2ROTATE,
	MOVER_2TO1ROTATE
} moverState_t;

typedef enum {
	MOD_UNKNOWN,
	MOD_SHOTGUN,
	MOD_GAUNTLET,
	MOD_MACHINEGUN,
	MOD_GRENADE,
	MOD_GRENADE_SPLASH,
	MOD_ROCKET,
	MOD_ROCKET_SPLASH,
	MOD_RAILGUN,
	MOD_LIGHTNING,
	MOD_BFG,
	MOD_BFG_SPLASH,
	MOD_KNIFE,
	MOD_KNIFE2,
	MOD_KNIFE_STEALTH,
	MOD_LUGER,
	MOD_COLT,
	MOD_MP40,
	MOD_THOMPSON,
	MOD_STEN,
	MOD_MAUSER,
	MOD_SNIPERRIFLE,
	MOD_GARAND,
	MOD_SNOOPERSCOPE,
	MOD_SILENCER,   //----(SA)
	MOD_AKIMBO,     //----(SA)
	MOD_BAR,    //----(SA)
	MOD_FG42,
	MOD_FG42SCOPE,
	MOD_PANZERFAUST,
	MOD_ROCKET_LAUNCHER,
	MOD_GRENADE_LAUNCHER,
	MOD_VENOM,
	MOD_VENOM_FULL,
	MOD_FLAMETHROWER,
	MOD_TESLA,
	MOD_SPEARGUN,
	MOD_SPEARGUN_CO2,
	MOD_GRENADE_PINEAPPLE,
	MOD_CROSS,
	MOD_MORTAR,
	MOD_MORTAR_SPLASH,
	MOD_KICKED,
	MOD_GRABBER,
	MOD_DYNAMITE,
	MOD_DYNAMITE_SPLASH,
	MOD_AIRSTRIKE, // JPW NERVE
	MOD_WATER,
	MOD_SLIME,
	MOD_LAVA,
	MOD_CRUSH,
	MOD_TELEFRAG,
	MOD_FALLING,
	MOD_SUICIDE,
	MOD_TARGET_LASER,
	MOD_TRIGGER_HURT,
	MOD_GRAPPLE,
	MOD_EXPLOSIVE,
	MOD_POISONGAS,
	MOD_ZOMBIESPIT,
	MOD_ZOMBIESPIT_SPLASH,
	MOD_ZOMBIESPIRIT,
	MOD_ZOMBIESPIRIT_SPLASH,
	MOD_LOPER_LEAP,
	MOD_LOPER_GROUND,
	MOD_LOPER_HIT,

	// JPW NERVE multiplayer class-specific MODs
	MOD_LT_ARTILLERY,
	MOD_LT_AIRSTRIKE,
	MOD_ENGINEER,   // not sure if we'll use
	MOD_MEDIC,      // these like this or not
//
MOD_BAT

} meansOfDeath_t;


//---------------------------------------------------------

// gitem_t->type
typedef enum {
	IT_BAD,
	IT_WEAPON,              // EFX: rotate + upscale + minlight

	IT_AMMO,                // EFX: rotate
	IT_ARMOR,               // EFX: rotate + minlight
	IT_HEALTH,              // EFX: static external sphere + rotating internal
	IT_POWERUP,             // instant on, timer based
							// EFX: rotate + external ring that rotates
							IT_HOLDABLE,            // single use, holdable item
													// EFX: rotate + bob
													IT_KEY,
													IT_TREASURE,            // gold bars, etc.  things that can be picked up and counted for a tally at end-level
													IT_CLIPBOARD,           // 'clipboard' used as a general term for 'popup' items where you pick up the item and it pauses and opens a menu
													IT_TEAM
} itemType_t;

#define MAX_ITEM_MODELS 5
#define MAX_ITEM_ICONS 4

// JOSEPH 4-17-00
typedef struct gitem_s {
	char        *classname; // spawning name
	char        *pickup_sound;
	char        *world_model[MAX_ITEM_MODELS];

	char        *icon;
	char        *ammoicon;
	char        *pickup_name;   // for printing on pickup

	int quantity;               // for ammo how much, or duration of powerup (value not necessary for ammo/health.  that value set in gameskillnumber[] below)
	itemType_t giType;          // IT_* flags

	int giTag;

	int giAmmoIndex;            // type of weapon ammo this uses.  (ex. WP_MP40 and WP_LUGER share 9mm ammo, so they both have WP_LUGER for giAmmoIndex)
	int giClipIndex;            // which clip this weapon uses.  this allows the sniper rifle to use the same clip as the garand, etc.

	char        *precaches;     // string of all models and images this item will use
	char        *sounds;        // string of all sounds this item will use

	int gameskillnumber[4];
} gitem_t;

struct gentity_s {
	entityState_t s;                // communicated by server to clients
	entityShared_t r;               // shared by both the server system and game

	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!
	//================================

	struct gclient_s    *client;            // NULL if not a client

	qboolean inuse;

	char        *classname;         // set in QuakeEd
	int spawnflags;                 // set in QuakeEd

	qboolean neverFree;             // if true, FreeEntity will only unlink
									// bodyque uses this

	int flags;                      // FL_* variables

	char        *model;
	char        *model2;
	int freetime;                   // level.time when the object was freed

	int eventTime;                  // events will be cleared EVENT_VALID_MSEC after set
	qboolean freeAfterEvent;
	qboolean unlinkAfterEvent;

	qboolean physicsObject;         // if true, it can be pushed by movers and fall off edges
									// all game items are physicsObjects,
	float physicsBounce;            // 1.0 = continuous bounce, 0.0 = no bounce
	int clipmask;                   // brushes with this content value will be collided against
									// when moving.  items and corpses do not collide against
									// players, for instance

	// movers
	moverState_t moverState;
	int soundPos1;
	int sound1to2;
	int sound2to1;
	int soundPos2;
	int soundLoop;
	// JOSEPH 1-26-00
	int sound2to3;
	int sound3to2;
	int soundPos3;
	// END JOSEPH

	int soundKicked;
	int soundKickedEnd;

	int soundSoftopen;
	int soundSoftendo;
	int soundSoftclose;
	int soundSoftendc;

	gentity_t   *parent;
	gentity_t   *nextTrain;
	gentity_t   *prevTrain;
	// JOSEPH 1-26-00
	vec3_t pos1, pos2, pos3;
	// END JOSEPH

	char        *message;

	int timestamp;              // body queue sinking, etc

	float angle;                // set in editor, -1 = up, -2 = down
	char        *target;
	char        *targetdeath;   // fire this on death exclusively //----(SA)	added
	char        *targetname;
	char        *team;
	char        *targetShaderName;
	char        *targetShaderNewName;
	gentity_t   *target_ent;

	float speed;
	float closespeed;           // for movers that close at a different speed than they open
	vec3_t movedir;

	int gDuration;
	int gDurationBack;
	vec3_t gDelta;
	vec3_t gDeltaBack;

	int nextthink;
	void(*think)(gentity_t *self);
	void(*reached)(gentity_t *self);       // movers call this when hitting endpoint
	void(*blocked)(gentity_t *self, gentity_t *other);
	void(*touch)(gentity_t *self, gentity_t *other, trace_t *trace);
	void(*use)(gentity_t *self, gentity_t *other, gentity_t *activator);
	void(*pain)(gentity_t *self, gentity_t *attacker, int damage, vec3_t point);
	void(*die)(gentity_t *self, gentity_t *inflictor, gentity_t *attacker, int damage, int mod);

	int pain_debounce_time;
	int fly_sound_debounce_time;            // wind tunnel
	int last_move_time;

	int health;

	qboolean takedamage;

	int damage;
	int splashDamage;           // quad will increase this without increasing radius
	int splashRadius;
	int methodOfDeath;
	int splashMethodOfDeath;

	int count;

	gentity_t   *chain;
	gentity_t   *enemy;
	gentity_t   *activator;
	gentity_t   *teamchain;     // next entity in team
	gentity_t   *teammaster;    // master of the team

	int watertype;
	int waterlevel;

	int noise_index;

	// timing variables
	float wait;
	float random;

	// Rafael - sniper variable
	// sniper uses delay, random, radius
	int radius;
	float delay;

	// JOSEPH 10-11-99
	int TargetFlag;
	float duration;
	vec3_t rotate;
	vec3_t TargetAngles;
	// END JOSEPH

	gitem_t     *item;          // for bonus items

	// Ridah, AI fields
	char        *aiAttributes;
	char        *aiName;
	int aiTeam;
	void(*AIScript_AlertEntity)(gentity_t *ent);
	qboolean aiInactive;
	int aiCharacter;            // the index of the type of character we are (from aicast_soldier.c)
	// done.

	char        *aiSkin;
	char        *aihSkin;

	vec3_t dl_color;
	char        *dl_stylestring;
	char        *dl_shader;
	int dl_atten;


	int key;                    // used by:  target_speaker->nopvs,

	qboolean active;
	qboolean botDelayBegin;

	// Rafael - mg42
	float harc;
	float varc;

	//----(SA)	added
	float activateArc;              // right now just for mg42, but available for setting what angle this ent can be touched/killed from

	int props_frame_state;

	// Ridah
	int missionLevel;                   // highest mission level completed (for previous level de-briefings)
	int missionObjectives;              // which objectives for the current level have been met
										// gets reset each new level

	int numSecretsFound;                //----(SA)	added to get into savegame
	int numTreasureFound;               //----(SA)	added to get into savegame

	// done.

	// Rafael
	qboolean is_dead;
	// done

	int start_size;
	int end_size;

	// Rafael props

	qboolean isProp;

	int mg42BaseEnt;

	gentity_t   *melee;

	char        *spawnitem;

	qboolean nopickup;

	int flameQuota, flameQuotaTime, flameBurnEnt;

	int count2;

	int grenadeExplodeTime;         // we've caught a grenade, which was due to explode at this time
	int grenadeFired;               // the grenade entity we last fired

	int mg42ClampTime;              // time to wait before an AI decides to ditch the mg42

	char        *track;

	// entity scripting system
	char                *scriptName;

	int numScriptEvents;
	g_script_event_t    *scriptEvents;  // contains a list of actions to perform for each event type
	g_script_status_t scriptStatus;     // current status of scripting
	g_script_status_t scriptStatusBackup;
	// the accumulation buffer
	int scriptAccumBuffer[G_MAX_SCRIPT_ACCUM_BUFFERS];

	qboolean AASblocking;
	float accuracy;

	char        *tagName;       // name of the tag we are attached to
	gentity_t   *tagParent;

	float headshotDamageScale;

	g_script_status_t scriptStatusCurrent;      // had to go down here to keep savegames compatible

	int emitID;                 //----(SA)	added
	int emitNum;                //----(SA)	added
	int emitPressure;           //----(SA)	added
	int emitTime;               //----(SA)	added

	// -------------------------------------------------------------------------------------------
	// if working on a post release patch, new variables should ONLY be inserted after this point
};

typedef enum {
	CON_DISCONNECTED,
	CON_CONNECTING,
	CON_CONNECTED
} clientConnected_t;

typedef enum {
	SPECTATOR_NOT,
	SPECTATOR_FREE,
	SPECTATOR_FOLLOW,
	SPECTATOR_SCOREBOARD
} spectatorState_t;

typedef enum {
	TEAM_BEGIN,     // Beginning a team game, spawn at base
	TEAM_ACTIVE     // Now actively playing
} playerTeamStateState_t;

typedef enum {
	TEAM_FREE,
	TEAM_RED,
	TEAM_BLUE,
	TEAM_SPECTATOR,

	TEAM_NUM_TEAMS
} team_t;

typedef struct {
	playerTeamStateState_t state;

	int location;

	int captures;
	int basedefense;
	int carrierdefense;
	int flagrecovery;
	int fragcarrier;
	int assists;

	float lasthurtcarrier;
	float lastreturnedflag;
	float flagsince;
	float lastfraggedcarrier;
} playerTeamState_t;

// the auto following clients don't follow a specific client
// number, but instead follow the first two active players
#define FOLLOW_ACTIVE1  -1
#define FOLLOW_ACTIVE2  -2

// client data that stays across multiple levels or tournament restarts
// this is achieved by writing all the data to cvar strings at game shutdown
// time and reading them back at connection time.  Anything added here
// MUST be dealt with in G_InitSessionData() / G_ReadSessionData() / G_WriteSessionData()
typedef struct {
	team_t sessionTeam;
	int spectatorTime;              // for determining next-in-line to play
	spectatorState_t spectatorState;
	int spectatorClient;            // for chasecam and follow mode
	int wins, losses;               // tournament stats
	int playerType;                 // DHM - Nerve :: for GT_WOLF
	int playerWeapon;               // DHM - Nerve :: for GT_WOLF
	int playerPistol;               // DHM - Nerve :: for GT_WOLF
	int playerItem;                 // DHM - Nerve :: for GT_WOLF
	int playerSkin;                 // DHM - Nerve :: for GT_WOLF
} clientSession_t;

//
#define MAX_NETNAME         36
#define MAX_VOTE_COUNT      3

#define PICKUP_ACTIVATE 0   // pickup items only when using "+activate"
#define PICKUP_TOUCH    1   // pickup items when touched
#define PICKUP_FORCE    2   // pickup the next item when touched (and reset to PICKUP_ACTIVATE when done)

// client data that stays across multiple respawns, but is cleared
// on each level change or team change at ClientBegin()
typedef struct {
	clientConnected_t connected;
	usercmd_t cmd;                  // we would lose angles if not persistant
	usercmd_t oldcmd;               // previous command processed by pmove()
	qboolean localClient;           // true if "ip" info key is "localhost"
	qboolean initialSpawn;          // the first spawn should be at a cool location
	qboolean predictItemPickup;     // based on cg_predictItems userinfo
	qboolean pmoveFixed;            //
	char netname[MAX_NETNAME];

	int autoActivate;               // based on cg_autoactivate userinfo		(uses the PICKUP_ values above)
	int emptySwitch;                // based on cg_emptyswitch userinfo (means "switch my weapon for me when ammo reaches '0' rather than -1)

	int maxHealth;                  // for handicapping
	int enterTime;                  // level.time the client entered the game
	playerTeamState_t teamState;    // status in teamplay games
	int voteCount;                  // to prevent people from constantly calling votes
	int teamVoteCount;              // to prevent people from constantly calling votes
	qboolean teamInfo;              // send team overlay updates?
} clientPersistant_t;


// this structure is cleared on each ClientSpawn(),
// except for 'client->pers' and 'client->sess'
struct gclient_s {
	// ps MUST be the first element, because the server expects it
	playerState_t ps;               // communicated by server to clients

	// the rest of the structure is private to game
	clientPersistant_t pers;
	clientSession_t sess;

	qboolean readyToExit;           // wishes to leave the intermission

	qboolean noclip;

	int lastCmdTime;                // level.time of last usercmd_t, for EF_CONNECTION
									// we can't just use pers.lastCommand.time, because
									// of the g_sycronousclients case
	int buttons;
	int oldbuttons;
	int latched_buttons;

	int wbuttons;
	int oldwbuttons;
	int latched_wbuttons;
	vec3_t oldOrigin;

	// sum up damage over an entire frame, so
	// shotgun blasts give a single big kick
	int damage_armor;               // damage absorbed by armor
	int damage_blood;               // damage taken out of health
	int damage_knockback;           // impact damage
	vec3_t damage_from;             // origin for vector calculation
	qboolean damage_fromWorld;      // if true, don't use the damage_from vector

	int accurateCount;              // for "impressive" reward sound

	int accuracy_shots;             // total number of shots
	int accuracy_hits;              // total number of hits

	//
	int lastkilled_client;          // last client that this client killed
	int lasthurt_client;            // last client that damaged this client
	int lasthurt_mod;               // type of damage the client did

	// timers
	int respawnTime;                // can respawn when time > this, force after g_forcerespwan
	int inactivityTime;             // kick players when time > this
	qboolean inactivityWarning;     // qtrue if the five seoond warning has been given
	int rewardTime;                 // clear the EF_AWARD_IMPRESSIVE, etc when time > this

	int airOutTime;

	int lastKillTime;               // for multiple kill rewards

	qboolean fireHeld;              // used for hook
	gentity_t   *hook;              // grapple hook if out

	int switchTeamTime;             // time the player switched teams

	// timeResidual is used to handle events that happen every second
	// like health / armor countdowns and regeneration
	int timeResidual;

	float currentAimSpreadScale;

	int medicHealAmt;

	// RF, may be shared by multiple clients/characters
	void *modelInfo;

	// -------------------------------------------------------------------------------------------
	// if working on a post release patch, new variables should ONLY be inserted after this point

	gentity_t   *persistantPowerup;
	int portalID;
	int ammoTimes[32];
	int invulnerabilityTime;

	gentity_t   *cameraPortal;              // grapple hook if out
	vec3_t cameraOrigin;

	int limboDropWeapon;         // JPW NERVE weapon to drop in limbo
	int deployQueueNumber;         // JPW NERVE player order in reinforcement FIFO queue
	int sniperRifleFiredTime;         // JPW NERVE last time a sniper rifle was fired (for muzzle flip effects)
	float sniperRifleMuzzleYaw;       // JPW NERVE for time-dependent muzzle flip in multiplayer
	float sniperRifleMuzzlePitch;       // (SA) added

	int saved_persistant[MAX_PERSISTANT];           // DHM - Nerve :: Save ps->persistant here during Limbo
};

#define MAX_ANIMSCRIPT_MODELS               32      // allocated dynamically, so limit is scalable
#define MAX_ANIMSCRIPT_ITEMS_PER_MODEL      256
#define MAX_MODEL_ANIMATIONS                256     // animations per model
#define MAX_ANIMSCRIPT_ANIMCOMMANDS         8
#define MAX_ANIMSCRIPT_ITEMS                32

// NOTE: these must all be in sync with string tables in bg_animation.c

typedef enum
{
	ANIM_MT_UNUSED,
	ANIM_MT_IDLE,
	ANIM_MT_IDLECR,
	ANIM_MT_WALK,
	ANIM_MT_WALKBK,
	ANIM_MT_WALKCR,
	ANIM_MT_WALKCRBK,
	ANIM_MT_RUN,
	ANIM_MT_RUNBK,
	ANIM_MT_SWIM,
	ANIM_MT_SWIMBK,
	ANIM_MT_STRAFERIGHT,
	ANIM_MT_STRAFELEFT,
	ANIM_MT_TURNRIGHT,
	ANIM_MT_TURNLEFT,
	ANIM_MT_CLIMBUP,
	ANIM_MT_CLIMBDOWN,

	NUM_ANIM_MOVETYPES
} scriptAnimMoveTypes_t;

typedef enum
{
	ANIM_ET_PAIN,
	ANIM_ET_DEATH,
	ANIM_ET_FIREWEAPON,
	ANIM_ET_JUMP,
	ANIM_ET_JUMPBK,
	ANIM_ET_LAND,
	ANIM_ET_DROPWEAPON,
	ANIM_ET_RAISEWEAPON,
	ANIM_ET_CLIMB_MOUNT,
	ANIM_ET_CLIMB_DISMOUNT,
	ANIM_ET_RELOAD,
	ANIM_ET_PICKUPGRENADE,
	ANIM_ET_KICKGRENADE,
	ANIM_ET_QUERY,
	ANIM_ET_INFORM_FRIENDLY_OF_ENEMY,
	ANIM_ET_KICK,
	ANIM_ET_REVIVE,
	ANIM_ET_FIRSTSIGHT,
	ANIM_ET_ROLL,
	ANIM_ET_FLIP,
	ANIM_ET_DIVE,
	ANIM_ET_PRONE_TO_CROUCH,
	ANIM_ET_BULLETIMPACT,
	ANIM_ET_INSPECTSOUND,
	ANIM_ET_SECONDLIFE,

	NUM_ANIM_EVENTTYPES
} scriptAnimEventTypes_t;

typedef enum
{
	ANIM_BP_UNUSED,
	ANIM_BP_LEGS,
	ANIM_BP_TORSO,
	ANIM_BP_BOTH,

	NUM_ANIM_BODYPARTS
} animBodyPart_t;

typedef enum
{
	ANIM_COND_WEAPON,
	ANIM_COND_ENEMY_POSITION,
	ANIM_COND_ENEMY_WEAPON,
	ANIM_COND_UNDERWATER,
	ANIM_COND_MOUNTED,
	ANIM_COND_MOVETYPE,
	ANIM_COND_UNDERHAND,
	ANIM_COND_LEANING,
	ANIM_COND_IMPACT_POINT,
	ANIM_COND_CROUCHING,
	ANIM_COND_STUNNED,
	ANIM_COND_FIRING,
	ANIM_COND_SHORT_REACTION,
	ANIM_COND_ENEMY_TEAM,
	ANIM_COND_PARACHUTE,
	ANIM_COND_CHARGING,
	ANIM_COND_SECONDLIFE,
	ANIM_COND_HEALTH_LEVEL,
	ANIM_COND_DEFENSE,
	ANIM_COND_SPECIAL_CONDITION,

	NUM_ANIM_CONDITIONS
} scriptAnimConditions_t;

//-------------------------------------------------------------------

typedef struct
{
	char    *string;
	int hash;
} animStringItem_t;

typedef struct
{
	int index;      // reference into the table of possible conditionals
	int value[2];       // can store anything from weapon bits, to position enums, etc
} animScriptCondition_t;

typedef struct
{
	short int bodyPart[2];      // play this animation on legs/torso/both
	short int animIndex[2];     // animation index in our list of animations
	short int animDuration[2];
	short int soundIndex;
	short int accShowBits;      //----(SA)	added
	short int accHideBits;      //----(SA)	added
} animScriptCommand_t;

typedef struct
{
	int numConditions;
	animScriptCondition_t conditions[NUM_ANIM_CONDITIONS];
	int numCommands;
	animScriptCommand_t commands[MAX_ANIMSCRIPT_ANIMCOMMANDS];
} animScriptItem_t;

typedef struct
{
	int numItems;
	animScriptItem_t    *items[MAX_ANIMSCRIPT_ITEMS];   // pointers into a global list of items
} animScript_t;

typedef enum { GENDER_MALE, GENDER_FEMALE, GENDER_NEUTER } gender_t;

typedef enum {
	FOOTSTEP_NORMAL,
	FOOTSTEP_BOOT,
	FOOTSTEP_FLESH,
	FOOTSTEP_MECH,
	FOOTSTEP_ENERGY,
	FOOTSTEP_METAL,
	FOOTSTEP_WOOD,
	FOOTSTEP_GRASS,
	FOOTSTEP_GRAVEL,
	// END JOSEPH
	FOOTSTEP_SPLASH,

	FOOTSTEP_ROOF,
	FOOTSTEP_SNOW,
	FOOTSTEP_CARPET,    //----(SA)	added

	FOOTSTEP_ELITE_STEP,
	FOOTSTEP_ELITE_METAL,
	FOOTSTEP_ELITE_ROOF,
	FOOTSTEP_ELITE_WOOD,
	FOOTSTEP_ELITE_GRAVEL,

	FOOTSTEP_SUPERSOLDIER_METAL,
	FOOTSTEP_SUPERSOLDIER_GRASS,
	FOOTSTEP_SUPERSOLDIER_GRAVEL,
	FOOTSTEP_SUPERSOLDIER_STEP,
	FOOTSTEP_SUPERSOLDIER_WOOD,

	FOOTSTEP_PROTOSOLDIER_METAL,
	FOOTSTEP_PROTOSOLDIER_GRASS,
	FOOTSTEP_PROTOSOLDIER_GRAVEL,
	FOOTSTEP_PROTOSOLDIER_STEP,
	FOOTSTEP_PROTOSOLDIER_WOOD,

	FOOTSTEP_LOPER_METAL,
	FOOTSTEP_LOPER_STEP,
	FOOTSTEP_LOPER_WOOD,

	FOOTSTEP_ZOMBIE_GRAVEL,
	FOOTSTEP_ZOMBIE_STEP,
	FOOTSTEP_ZOMBIE_WOOD,

	FOOTSTEP_BEAST,

	FOOTSTEP_HEINRICH,

	FOOTSTEP_TOTAL
} footstep_t;

#define ANIMFL_LADDERANIM   0x1
#define ANIMFL_FIRINGANIM   0x2

typedef struct animation_s {
	char name[MAX_QPATH];
	int firstFrame;
	int numFrames;
	int loopFrames;             // 0 to numFrames
	int frameLerp;              // msec between frames
	int initialLerp;            // msec to get to first frame
	int moveSpeed;
	int animBlend;              // take this long to blend to next anim
	int priority;
	//
	// derived
	//
	int duration;
	int nameHash;
	int flags;
	int movetype;
	float stepGap;
} animation_t;

// Ridah, head animations
typedef enum {
	HEAD_NEUTRAL_CLOSED,
	HEAD_NEUTRAL_A,
	HEAD_NEUTRAL_O,
	HEAD_NEUTRAL_I,
	HEAD_NEUTRAL_E,
	HEAD_HAPPY_CLOSED,
	HEAD_HAPPY_O,
	HEAD_HAPPY_I,
	HEAD_HAPPY_E,
	HEAD_HAPPY_A,
	HEAD_ANGRY_CLOSED,
	HEAD_ANGRY_O,
	HEAD_ANGRY_I,
	HEAD_ANGRY_E,
	HEAD_ANGRY_A,

	MAX_HEAD_ANIMS
} animHeadNumber_t;

typedef struct headAnimation_s {
	int firstFrame;
	int numFrames;
} headAnimation_t;

typedef struct
{
	char modelname[MAX_QPATH];                              // name of the model

	// parsed from the start of the cfg file
	gender_t gender;
	footstep_t footsteps;
	vec3_t headOffset;
	int version;
	qboolean isSkeletal;

	// parsed from cfg file
	animation_t animations[MAX_MODEL_ANIMATIONS];           // anim names, frame ranges, etc
	headAnimation_t headAnims[MAX_HEAD_ANIMS];
	int numAnimations, numHeadAnims;

	// parsed from script file
	animScript_t scriptAnims[MAX_AISTATES][NUM_ANIM_MOVETYPES];             // locomotive anims, etc
	animScript_t scriptCannedAnims[MAX_AISTATES][NUM_ANIM_MOVETYPES];       // played randomly
	animScript_t scriptStateChange[MAX_AISTATES][MAX_AISTATES];             // state change events
	animScript_t scriptEvents[NUM_ANIM_EVENTTYPES];                         // events that trigger special anims

	// global list of script items for this model
	animScriptItem_t scriptItems[MAX_ANIMSCRIPT_ITEMS_PER_MODEL];
	int numScriptItems;

} animModelInfo_t;

// this is the main structure that is duplicated on the client and server
typedef struct
{
	int clientModels[MAX_CLIENTS];                      // so we know which model each client is using
	animModelInfo_t     *modelInfo[MAX_ANIMSCRIPT_MODELS];
	int clientConditions[MAX_CLIENTS][NUM_ANIM_CONDITIONS][2];
	//
	// pointers to functions from the owning module
	//
	int(*soundIndex)(const char *name);
	void(*playSound)(int soundIndex, vec3_t org, int clientNum);
} animScriptData_t;


//
// this structure is cleared as each map is entered
//
#define MAX_SPAWN_VARS          64
#define MAX_SPAWN_VARS_CHARS    2048

typedef struct {
	struct gclient_s    *clients;       // [maxclients]

	struct gentity_s    *gentities;
	int gentitySize;
	int num_entities;               // current number, <= MAX_GENTITIES

	int warmupTime;                 // restart match at this time

	fileHandle_t logFile;

	// store latched cvars here that we want to get at often
	int maxclients;

	int framenum;
	int time;                           // in msec
	int previousTime;                   // so movers can back up when blocked

	int startTime;                      // level.time the map was started

	int teamScores[TEAM_NUM_TEAMS];
	int lastTeamLocationTime;               // last time of client team location update

	qboolean newSession;                // don't use any old session data, because
										// we changed gametype

	qboolean restarted;                 // waiting for a map_restart to fire

	int numConnectedClients;
	int numNonSpectatorClients;         // includes connecting clients
	int numPlayingClients;              // connected, non-spectators
	int sortedClients[MAX_CLIENTS];             // sorted by score
	int follow1, follow2;               // clientNums for auto-follow spectators

	int snd_fry;                        // sound index for standing in lava

	int warmupModificationCount;            // for detecting if g_warmup is changed

	// voting state
	char voteString[MAX_STRING_CHARS];
	char voteDisplayString[MAX_STRING_CHARS];
	int voteTime;                       // level.time vote was called
	int voteExecuteTime;                // time the vote is executed
	int voteYes;
	int voteNo;
	int numVotingClients;               // set by CalculateRanks

	// team voting state
	char teamVoteString[2][MAX_STRING_CHARS];
	int teamVoteTime[2];                // level.time vote was called
	int teamVoteYes[2];
	int teamVoteNo[2];
	int numteamVotingClients[2];        // set by CalculateRanks

	// spawn variables
	qboolean spawning;                  // the G_Spawn*() functions are valid
	int numSpawnVars;
	char        *spawnVars[MAX_SPAWN_VARS][2];  // key / value pairs
	int numSpawnVarChars;
	char spawnVarChars[MAX_SPAWN_VARS_CHARS];

	// intermission state
	int intermissionQueued;             // intermission was qualified, but
										// wait INTERMISSION_DELAY_TIME before
										// actually going there so the last
										// frag can be watched.  Disable future
										// kills during this delay
	int intermissiontime;               // time the intermission was started
	char        *changemap;
	qboolean readyToExit;               // at least one client wants to exit
	int exitTime;
	vec3_t intermission_origin;         // also used for spectator spawns
	vec3_t intermission_angle;

	qboolean locationLinked;            // target_locations get linked
	gentity_t   *locationHead;          // head of the location list
	int bodyQueIndex;                   // dead bodies
	gentity_t   *bodyQue[8];

	int portalSequence;
	// Ridah
	char        *scriptAI;
	int reloadPauseTime;                // don't think AI/client's until this time has elapsed
	int reloadDelayTime;                // don't start loading the savegame until this has expired

	int lastGrenadeKick;

	int loperZapSound;
	int stimSoldierFlySound;
	int bulletRicochetSound;
	// done.

	int snipersound;

	//----(SA)	added
	int numSecrets;
	int numTreasure;
	int numArtifacts;
	int numObjectives;
	//----(SA)	end

	int knifeSound[4];

	// JPW NERVE
	int redReinforceTime, blueReinforceTime;         // last time reinforcements arrived in ms
	int redNumWaiting, blueNumWaiting;         // number of reinforcements in queue
	vec3_t spawntargets[MAX_MULTI_SPAWNTARGETS];      // coordinates of spawn targets
	int numspawntargets;         // # spawntargets in this map
// jpw

	// RF, entity scripting
	char        *scriptEntity;

	// player/AI model scripting (server repository)
	animScriptData_t animScriptData;

	// next map to load
	char nextMap[MAX_STRING_CHARS];

	// RF, record last time we loaded, so we can hack around sighting issues on reload
	int lastLoadTime;

} level_locals_t;

typedef enum
{
	AICHAR_NONE,

	AICHAR_SOLDIER,
	AICHAR_AMERICAN,
	AICHAR_ZOMBIE,
	AICHAR_WARZOMBIE,
	AICHAR_VENOM,
	AICHAR_LOPER,
	AICHAR_ELITEGUARD,
	AICHAR_STIMSOLDIER1,    // dual machineguns
	AICHAR_STIMSOLDIER2,    // rocket in left hand
	AICHAR_STIMSOLDIER3,    // tesla in left hand
	AICHAR_SUPERSOLDIER,
	AICHAR_BLACKGUARD,
	AICHAR_PROTOSOLDIER,

	AICHAR_FROGMAN,
	AICHAR_HELGA,
	AICHAR_HEINRICH,    //----(SA)	added

	AICHAR_PARTISAN,
	AICHAR_CIVILIAN,

	NUM_CHARACTERS
} AICharacters_t;
// done.



// NOTE: we can only use up to 15 in the client-server stream
// SA NOTE: should be 31 now (I added 1 bit in msg.c)
typedef enum {
	WP_NONE,                // 0

	WP_KNIFE,               // 1
	// German weapons
	WP_LUGER,               // 2
	WP_MP40,                // 3
	WP_MAUSER,              // 4
	WP_FG42,                // 5
	WP_GRENADE_LAUNCHER,    // 6
	WP_PANZERFAUST,         // 7
	WP_VENOM,               // 8
	WP_FLAMETHROWER,        // 9
	WP_TESLA,               // 10
//	WP_SPEARGUN,			// 11

// weapon keys only go 1-0, so put the alternates above that (since selection will be a double click on the german weapon key)

	// American equivalents
//	WP_KNIFE2,				// 12
WP_COLT,                // 11	equivalent american weapon to german luger
WP_THOMPSON,            // 12	equivalent american weapon to german mp40
WP_GARAND,              // 13	equivalent american weapon to german mauser
//	WP_BAR,					// 16	equivalent american weapon to german fg42
WP_GRENADE_PINEAPPLE,   // 14
//	WP_ROCKET_LAUNCHER,		// 18	equivalent american weapon to german panzerfaust

	// secondary fire weapons
	WP_SNIPERRIFLE,         // 15
	WP_SNOOPERSCOPE,        // 16
//	WP_VENOM_FULL,			// 21
//	WP_SPEARGUN_CO2,		// 22
WP_FG42SCOPE,           // 17	fg42 alt fire
//	WP_BAR2,				// 24

	// more weapons
	WP_STEN,                // 18	silenced sten sub-machinegun
	WP_SILENCER,            // 19	// used to be sp5
	WP_AKIMBO,              // 20	//----(SA)	added

	// specialized/one-time weapons
// JPW NERVE -- swapped mortar & antitank (unused?) and added class_special
WP_CLASS_SPECIAL,       // 21	// class-specific multiplayer weapon (airstrike, engineer, or medpack)
// (SA) go ahead and take the 'freezeray' spot.  it ain't happenin
//      (I checked for instances of WP_CLASS_SPECIAL and I don't think this'll cause you a problem.  however, if it does, move it where you need to. ) (SA)
// jpw
//	WP_CROSS,				// 29
WP_DYNAMITE,            // 22
//	WP_DYNAMITE2,			// 31
//	WP_PROX,				// 32

WP_MONSTER_ATTACK1,     // 23	// generic monster attack, slot 1
WP_MONSTER_ATTACK2,     // 24	// generic monster attack, slot 2
WP_MONSTER_ATTACK3,     // 25	// generic monster attack, slot 2

WP_GAUNTLET,            // 26

WP_SNIPER,              // 27
WP_GRENADE_SMOKE,       // 28	// smoke grenade for LT multiplayer
WP_MEDIC_HEAL,          // 29	// DHM - Nerve :: Medic special weapon
WP_MORTAR,              // 30

VERYBIGEXPLOSION,       // 31	// explosion effect for airplanes

WP_NUM_WEAPONS          // 32   NOTE: this cannot be larger than 64 for AI/player weapons!

} weapon_t;

typedef enum {
	ACC_BELT_LEFT,  // belt left (lower)
	ACC_BELT_RIGHT, // belt right (lower)
	ACC_BELT,       // belt (upper)
	ACC_BACK,       // back (upper)
	ACC_WEAPON,     // weapon (upper)
	ACC_WEAPON2,    // weapon2 (upper)
	ACC_HAT,        // hat (head)
	ACC_MOUTH2,     //
	ACC_MOUTH3,     //
	//
	ACC_MAX     // this is bound by network limits, must change network stream to increase this
				// (SA) No, really?  that's not true is it?  isn't this client-side only?
} accType_t;

#define ACC_NUM_MOUTH 3 // matches the above count (hat/mouth2/mouth3)

// each client has an associated clientInfo_t
// that contains media references necessary to present the
// client model and other color coded effects
// this is regenerated each time a client's configstring changes,
// usually as a result of a userinfo (name, model, etc) change
#define MAX_CUSTOM_SOUNDS   32
#define MAX_GIB_MODELS      16
typedef struct {
	qboolean infoValid;

	int clientNum;

	char name[MAX_QPATH];
	team_t team;

	int botSkill;                   // 0 = not bot, 1-5 = bot

	vec3_t color;

	int score;                      // updated by score servercmds
	int location;                   // location index for team mode
	int health;                     // you only get this info about your teammates
	int armor;
	int curWeapon;

	int handicap;
	int wins, losses;               // in tourney mode

	int powerups;                   // so can display quad/flag status

	int breathPuffTime;

	// when clientinfo is changed, the loading of models/skins/sounds
	// can be deferred until you are dead, to prevent hitches in
	// gameplay
	char modelName[MAX_QPATH];
	char skinName[MAX_QPATH];
	char hSkinName[MAX_QPATH];
	qboolean deferred;

	qhandle_t legsModel;
	qhandle_t legsSkin;

	qhandle_t torsoModel;
	qhandle_t torsoSkin;

	qboolean isSkeletal;

	//----(SA) added accessory models/skins for belts/backpacks/etc.
	qhandle_t accModels[ACC_MAX];       // see def of ACC_MAX for index descriptions
	qhandle_t accSkins[ACC_MAX];        // FIXME: put the #define for number of accessory models somewhere. (SA)

	//----(SA)	additional parts for specialized characters (the loper's spinning trunk for example)
	qhandle_t partModels[9];        // [0-7] are optionally called in scripts, [8] is reserved for internal use
	qhandle_t partSkins[9];
	//----(SA)	end

	qhandle_t headModel;
	qhandle_t headSkin;

	qhandle_t modelIcon;

	// RF, may be shared by multiple clients/characters
	animModelInfo_t *modelInfo;

	sfxHandle_t sounds[MAX_CUSTOM_SOUNDS];

	qhandle_t gibModels[MAX_GIB_MODELS];

	vec3_t playermodelScale;            //----(SA)	set in the skin.  client-side only

	int blinkTime;              //----(SA)
} clientInfo_t;


// weapon grouping
#define MAX_WEAP_BANKS      12
#define MAX_WEAPS_IN_BANK   3
// JPW NERVE
#define MAX_WEAPS_IN_BANK_MP    8
#define MAX_WEAP_BANKS_MP   7
// jpw
#define MAX_WEAP_ALTS       WP_DYNAMITE


// bit field limits
#define MAX_STATS               16
#define MAX_PERSISTANT          16
#define MAX_POWERUPS            16
#define MAX_WEAPONS             64  // (SA) and yet more!
#define MAX_HOLDABLE            16

typedef enum {
	W_PART_1,
	W_PART_2,
	W_PART_3,
	W_PART_4,
	W_PART_5,
	W_PART_6,
	W_PART_7,
	W_MAX_PARTS
} barrelType_t;

typedef enum {
	W_TP_MODEL,         //	third person model
	W_FP_MODEL,         //	first person model
	W_PU_MODEL,         //	pickup model
	W_FP_MODEL_SWAP,    //	swap out model
	W_SKTP_MODEL,       //	SKELETAL version third person model
	W_NUM_TYPES
} modelViewType_t;

typedef enum {
	WEAP_IDLE1,
	WEAP_IDLE2,
	WEAP_ATTACK1,
	WEAP_ATTACK2,
	WEAP_ATTACK_LASTSHOT,   // used when firing the last round before having an empty clip.
	WEAP_DROP,
	WEAP_RAISE,
	WEAP_RELOAD1,
	WEAP_RELOAD2,
	WEAP_RELOAD3,
	WEAP_ALTSWITCHFROM, // switch from alt fire mode weap (scoped/silencer/etc)
	WEAP_ALTSWITCHTO,   // switch to alt fire mode weap
	MAX_WP_ANIMATIONS
} weapAnimNumber_t;

typedef enum {
	WPOS_HIGH,
	WPOS_LOW,
	WPOS_KNIFE,
	WPOS_PISTOL,
	WPOS_SHOULDER,
	WPOS_THROW,
	WPOS_NUM_POSITIONS
} pose_t;

typedef struct {
	int oldFrame;
	int oldFrameTime;               // time when ->oldFrame was exactly on

	int frame;
	int frameTime;                  // time when ->frame will be exactly on

	float backlerp;

	float yawAngle;
	qboolean yawing;
	float pitchAngle;
	qboolean pitching;

	int animationNumber;            // may include ANIM_TOGGLEBIT
	int oldAnimationNumber;         // may include ANIM_TOGGLEBIT
	animation_t *animation;
	int animationTime;              // time when the first frame of the animation will be exact

	// Ridah, variable speed anims
	vec3_t oldFramePos;
	float animSpeedScale;
	int oldFrameSnapshotTime;
	headAnimation_t *headAnim;
	// done.

	animation_t *cgAnim;    // pointer to the root of the animation array to use (*animation above points at the current sequence)	//----(SA)	added
} lerpFrame_t;

#define MAX_ZOMBIE_SPIRITS          4
#define MAX_ZOMBIE_DEATH_TRAILS     16

#define MAX_LOPER_LIGHTNING_POINTS  24

#define MAX_TESLA_BOLTS             4

#define MAX_EFFECT_ENTS             20

typedef struct {
	lerpFrame_t legs, torso;

	// Ridah, talking animations
	lerpFrame_t head;
	// done.

	lerpFrame_t weap;       //----(SA)	autonomous weapon animations

	int lastTime;                   // last time we were processed/ If the time goes backwards, reset.

	int painTime;
	int painDuration;
	int painDirection;              // flip from 0 to 1
	int painAnimTorso;
	int painAnimLegs;
	int lightningFiring;

	// railgun trail spawning
	vec3_t railgunImpact;
	qboolean railgunFlash;

	// machinegun spinning
	float barrelAngle;
	int barrelTime;
	qboolean barrelSpinning;

	//----(SA) machinegun bolt sliding
	float boltPosition;
	int boltTime;
	int boltSliding;
	//----(SA) end

	//----(SA) 'spinner' spinning (body part)
	float spinnerAngle;
	int spinnerTime;
	qboolean spinnerSpinning;
	//----(SA)	end

	// Ridah, so we can do fast tag grabbing
	refEntity_t legsRefEnt, torsoRefEnt, headRefEnt, gunRefEnt;
	int gunRefEntFrame;

	float animSpeed;            // for manual adjustment

	// Zombie spirit effect
	// !!FIXME: these effects will be restarted by a *_restart command, can we save this data somehow?
	qboolean cueZombieSpirit;               // if this is qfalse, and the zombie effect flag is set, then we need to start a new attack
	int zombieSpiritStartTime;              // time the effect was started, so we can fade things in
	int zombieSpiritTrailHead[MAX_ZOMBIE_SPIRITS];
	int zombieSpiritRotationTimes[MAX_ZOMBIE_SPIRITS];
	int zombieSpiritRadiusCycleTimes[MAX_ZOMBIE_SPIRITS];
	int lastZombieSpirit;
	int nextZombieSpiritSound;
	int zombieSpiritEndTime;                // time the effect was disabled
	vec3_t zombieSpiritPos[MAX_ZOMBIE_SPIRITS];
	vec3_t zombieSpiritDir[MAX_ZOMBIE_SPIRITS];
	float zombieSpiritSpeed[MAX_ZOMBIE_SPIRITS];
	int zombieSpiritStartTimes[MAX_ZOMBIE_SPIRITS];

	// Zombie death effect
	// !!FIXME: these effects will be restarted by a *_restart command, can we save this data somehow?
	qboolean cueZombieDeath;            // if this is qfalse, and the zombie effect flag is set, then we need to start a new attack
	int zombieDeathStartTime;               // time the effect was started, so we can fade things in
	int zombieDeathEndTime;             // time the effect was disabled
	int lastZombieDeath;
	int zombieDeathFadeStart;
	int zombieDeathFadeEnd;
	int zombieDeathTrailHead[MAX_ZOMBIE_DEATH_TRAILS];
	int zombieDeathRotationTimes[MAX_ZOMBIE_DEATH_TRAILS];
	int zombieDeathRadiusCycleTimes[MAX_ZOMBIE_DEATH_TRAILS];

	// loper effects
	int loperLastGroundChargeTime;
	byte loperGroundChargeToggle;
	int loperGroundValidTime;

	vec3_t headLookIdeal;
	vec3_t headLookOffset;
	float headLookSpeed;
	int headLookStopTime;
	float headLookSpeedMax;

	// tesla coil effects
	vec3_t teslaEndPoints[MAX_TESLA_BOLTS];
	int teslaEndPointTimes[MAX_TESLA_BOLTS];            // time the bolt stays valid
	vec3_t teslaOffsetDirs[MAX_TESLA_BOLTS];            // bending direction from center or direct beam
	float teslaOffsets[MAX_TESLA_BOLTS];                // amount to offset from center
	int teslaOffsetTimes[MAX_TESLA_BOLTS];              // time the offset stays valid
	int teslaEnemy[MAX_TESLA_BOLTS];
	int teslaDamageApplyTime;

	int teslaDamagedTime;                   // time we were last hit by a tesla bolt

	// misc effects
	int effectEnts[MAX_EFFECT_ENTS];
	int numEffectEnts;
	int effect1EndTime;
	vec3_t lightningPoints[MAX_LOPER_LIGHTNING_POINTS];
	int lightningTimes[MAX_LOPER_LIGHTNING_POINTS];
	int lightningSoundTime;

	qboolean forceLOD;

} playerEntity_t;

// centity_t have a direct corespondence with gentity_t in the game, but
// only the entityState_t is directly communicated to the cgame
typedef struct centity_s {
	entityState_t currentState;     // from cg.frame
	entityState_t nextState;        // from cg.nextFrame, if available
	qboolean interpolate;           // true if next is valid to interpolate to
	qboolean currentValid;          // true if cg.frame holds this entity

	int muzzleFlashTime;                // move to playerEntity?
	int overheatTime;
	int previousEvent;
	int previousEventSequence;              // Ridah
	int teleportFlag;

	int trailTime;                  // so missile trails can handle dropped initial packets
	int miscTime;

	playerEntity_t pe;

	int errorTime;                  // decay the error from this time
	vec3_t errorOrigin;
	vec3_t errorAngles;

	qboolean extrapolated;          // false if origin / angles is an interpolation
	vec3_t rawOrigin;
	vec3_t rawAngles;

	vec3_t beamEnd;

	// exact interpolated position of entity on this frame
	vec3_t lerpOrigin;
	vec3_t lerpAngles;

	vec3_t lastLerpAngles;          // (SA) for remembering the last position when a state changes

	// Ridah, trail effects
	int headJuncIndex, headJuncIndex2;
	int lastTrailTime;
	// done.

	// Ridah
	float loopSoundVolume;
	vec3_t fireRiseDir;             // if standing still this will be up, otherwise it'll point away from movement dir
	int lastWeaponClientFrame;
	int lastFuseSparkTime;
	vec3_t lastFuseSparkOrg;

	// client side dlights
	int dl_frame;
	int dl_oldframe;
	float dl_backlerp;
	int dl_time;
	char dl_stylestring[64];
	int dl_sound;
	int dl_atten;

	lerpFrame_t lerpFrame;      //----(SA)	added
	vec3_t highlightOrigin;             // center of the geometry.  for things like corona placement on treasure
	qboolean usehighlightOrigin;

	refEntity_t refEnt;
	int processedFrame;                 // frame we were last added to the scene

	// client-side lightning
	int boltTimes[MAX_TESLA_BOLTS];
	vec3_t boltLocs[MAX_TESLA_BOLTS];
	vec3_t boltCrawlDirs[MAX_TESLA_BOLTS];

	// item highlighting

	int highlightTime;
	qboolean highlighted;

	animation_t centAnim[2];

	// (SA) added to help akimbo effects attach to the correct model
	qboolean akimboFire;
} centity_t;


// each WP_* weapon enum has an associated weaponInfo_t
// that contains media references necessary to present the
// weapon and its effects
typedef struct weaponInfo_s {
	qboolean registered;
	gitem_t         *item;

	//----(SA)	weapon animation sequences loaded from the weapon.cfg
	animation_t weapAnimations[MAX_WP_ANIMATIONS];
	//----(SA)	end

	qhandle_t handsModel;               // the hands don't actually draw, they just position the weapon

	qhandle_t standModel;               // not drawn.  tags used for positioning weapons for pickup

//----(SA) mod for 1st/3rd person weap views
	qhandle_t weaponModel[W_NUM_TYPES];
	qhandle_t wpPartModels[W_NUM_TYPES][W_MAX_PARTS];
	qhandle_t flashModel[W_NUM_TYPES];
	qhandle_t modModel[W_NUM_TYPES];        // like the scope for the rifles
//----(SA) end

	pose_t position;                    // wolf locations (high, low, knife, pistol, shoulder, throw)  defines are WPOS_HIGH, WPOS_LOW, WPOS_KNIFE, WPOS_PISTOL, WPOS_SHOULDER, WPOS_THROW

	vec3_t weaponMidpoint;              // so it will rotate centered instead of by tag

	float flashDlight;
	vec3_t flashDlightColor;
	sfxHandle_t flashSound[4];          // fast firing weapons randomly choose
	sfxHandle_t flashEchoSound[4];      //----(SA)	added - distant gun firing sound
	sfxHandle_t lastShotSound[4];       // sound of the last shot can be different (mauser doesn't have bolt action on last shot for example)

	sfxHandle_t switchSound[4];     //----(SA)	added

	qhandle_t weaponIcon[2];            //----(SA)	[0] is weap icon, [1] is highlight icon
	qhandle_t ammoIcon;

	qhandle_t ammoModel;

	qhandle_t missileModel;
	sfxHandle_t missileSound;
	void(*missileTrailFunc)(centity_t *, const struct weaponInfo_s *wi);
	float missileDlight;
	vec3_t missileDlightColor;
	int missileRenderfx;

	void(*ejectBrassFunc)(centity_t *);

	float trailRadius;
	float wiTrailTime;

	sfxHandle_t readySound;             // an amibient sound the weapon makes when it's /not/ firing
	sfxHandle_t firingSound;
	sfxHandle_t overheatSound;
	sfxHandle_t reloadSound;

	sfxHandle_t spinupSound;        //----(SA)	added // sound started when fire button goes down, and stepped on when the first fire event happens
	sfxHandle_t spindownSound;      //----(SA)	added // sound called if the above is running but player doesn't follow through and fire
} weaponInfo_t;


// each IT_* item has an associated itemInfo_t
// that constains media references necessary to present the
// item and its effects
typedef struct {
	qboolean registered;
	qhandle_t models[MAX_ITEM_MODELS];
	qhandle_t icons[MAX_ITEM_ICONS];
} itemInfo_t;


typedef struct {
	int itemNum;
} powerupInfo_t;

#define MAX_VIEWDAMAGE  8
typedef struct {
	int damageTime, damageDuration;
	float damageX, damageY, damageValue;
} viewDamage_t;

#define MAX_CAMERA_SHAKE    4
typedef struct {
	int time;
	float scale;
	float length;
	float radius;
	vec3_t src;
} cameraShake_t;

//======================================================================

// all cg.stepTime, cg.duckTime, cg.landTime, etc are set to cg.time when the action
// occurs, and they will have visible effects for #define STEP_TIME or whatever msec after

#define MAX_PREDICTED_EVENTS    16

typedef struct {
	int snapFlags;                      // SNAPFLAG_RATE_DELAYED, etc
	int ping;

	int serverTime;                 // server time the message is valid for (in msec)

	byte areamask[MAX_MAP_AREA_BYTES];                  // portalarea visibility bits

	playerState_t ps;                       // complete information about the current player at this time

	int numEntities;                        // all of the entities that need to be presented
	entityState_t entities[256];			// at the time of this snapshot

	int numServerCommands;                  // text based server commands to execute when this
	int serverCommandSequence;              // snapshot becomes current
} snapshot_t;

typedef struct {
	int client;
	int score;
	int ping;
	int time;
	int scoreFlags;
	int powerUps;
	int accuracy;
	int impressiveCount;
	int excellentCount;
	int guantletCount;
	int defendCount;
	int assistCount;
	int captures;
	qboolean perfect;
	int team;
} score_t;

typedef struct {
	int clientFrame;                // incremented each frame

	int clientNum;

	qboolean demoPlayback;
	qboolean levelShot;             // taking a level menu screenshot
	int deferredPlayerLoading;
	qboolean loading;               // don't defer players at initial startup
	qboolean intermissionStarted;       // don't play voice rewards, because game will end shortly

	// there are only one or two snapshot_t that are relevent at a time
	int latestSnapshotNum;          // the number of snapshots the client system has received
	int latestSnapshotTime;         // the time from latestSnapshotNum, so we don't need to read the snapshot yet

	snapshot_t  *snap;              // cg.snap->serverTime <= cg.time
	snapshot_t  *nextSnap;          // cg.nextSnap->serverTime > cg.time, or NULL
	snapshot_t activeSnapshots[2];

	float frameInterpolation;       // (float)( cg.time - cg.frame->serverTime ) / (cg.nextFrame->serverTime - cg.frame->serverTime)

	qboolean thisFrameTeleport;
	qboolean nextFrameTeleport;

	int frametime;              // cg.time - cg.oldTime

	int time;                   // this is the time value that the client
								// is rendering at.
	int oldTime;                // time at last frame, used for missile trails and prediction checking

	int physicsTime;            // either cg.snap->time or cg.nextSnap->time

	int timelimitWarnings;          // 5 min, 1 min, overtime
	int fraglimitWarnings;

	qboolean mapRestart;            // set on a map restart to set back the weapon

	qboolean renderingThirdPerson;          // during deaths, chasecams, etc

	// prediction state
	qboolean hyperspace;                // true if prediction has hit a trigger_teleport
	playerState_t predictedPlayerState;
	centity_t predictedPlayerEntity;
	qboolean validPPS;                  // clear until the first call to CG_PredictPlayerState
	int predictedErrorTime;
	vec3_t predictedError;

	int eventSequence;
	int predictableEvents[MAX_PREDICTED_EVENTS];

	float stepChange;                   // for stair up smoothing
	int stepTime;

	float duckChange;                   // for duck viewheight smoothing
	int duckTime;

	float landChange;                   // for landing hard
	int landTime;

	// input state sent to server
	int weaponSelect;
	int holdableSelect;                 // (SA) which holdable item is currently held ("selected").  When the client is ready to use it, send "use item <holdableSelect>"

	// auto rotating items
	vec3_t autoAnglesSlow;
	vec3_t autoAxisSlow[3];
	vec3_t autoAngles;
	vec3_t autoAxis[3];
	vec3_t autoAnglesFast;
	vec3_t autoAxisFast[3];

	// view rendering
	refdef_t refdef;
	vec3_t refdefViewAngles;            // will be converted to refdef.viewaxis

	// zoom key
	qboolean zoomed;
	qboolean zoomedBinoc;
	int zoomedScope;            //----(SA)	changed to int
	int zoomTime;
	float zoomSensitivity;
	float zoomval;


	// information screen text during loading
	unsigned char infoScreenText[MAX_STRING_CHARS];

	// scoreboard
	int scoresRequestTime;
	int numScores;
	int selectedScore;
	int teamScores[2];
	score_t scores[MAX_CLIENTS];
	qboolean showScores;
	qboolean scoreBoardShowing;
	int scoreFadeTime;
	char killerName[MAX_NAME_LENGTH];
	char spectatorList[MAX_STRING_CHARS];                   // list of names
	int spectatorLen;                                                           // length of list
	float spectatorWidth;                                                   // width in device units
	int spectatorTime;                                                      // next time to offset
	int spectatorPaintX;                                                    // current paint x
	int spectatorPaintX2;                                                   // current paint x
	int spectatorOffset;                                                    // current offset from start
	int spectatorPaintLen;                                              // current offset from start

	qboolean showItems;
	int itemFadeTime;

	qboolean lightstylesInited;

	// centerprinting
	int centerPrintTime;
	int centerPrintCharWidth;
	int centerPrintY;
	unsigned char centerPrint[1024];
	int centerPrintLines;

	// fade in/out
	int fadeTime;
	float fadeRate;
	vec4_t fadeColor1;
	vec4_t fadeColor2;

	//----(SA)	added
		// game stats
	int exitStatsTime;
	int exitStatsFade;
	// just a copy of what's on the server, updated by configstring.  better way to communicate/store this I'm sure
	int playTimeH;
	int playTimeM;
	int playTimeS;
	int attempts;
	int numObjectives;
	int numObjectivesFound;
	int numSecrets;
	int numSecretsFound;
	int numTreasure;
	int numTreasureFound;
	int numArtifacts;
	int numArtifactsFound;
	//----(SA)	end


		// low ammo warning state
	int lowAmmoWarning;             // 1 = low, 2 = empty

	// kill timers for carnage reward
	int lastKillTime;

	// crosshair client ID
	int crosshairClientNum;
	int crosshairClientTime;

	int crosshairPowerupNum;
	int crosshairPowerupTime;

	//----(SA)	added
		// cursorhints
	int cursorHintIcon;
	int cursorHintTime;
	int cursorHintFade;
	int cursorHintValue;

	//----(SA)	end

		// powerup active flashing
	int powerupActive;
	int powerupTime;

	// attacking player
	int attackerTime;
	int voiceTime;

	// reward medals
	int rewardTime;
	int rewardCount;
	qhandle_t rewardShader;

	// warmup countdown
	int warmup;
	int warmupCount;

	// message icon popup time	//----(SA)	added
	int yougotmailTime;

	//==========================

	int itemPickup;
	int itemPickupTime;
	int itemPickupBlendTime;            // the pulse around the crosshair is timed seperately

	int holdableSelectTime;             //----(SA)	for holdable item icon drawing

	int weaponSelectTime;
	int weaponAnimation;
	int weaponAnimationTime;

	// blend blobs
	viewDamage_t viewDamage[MAX_VIEWDAMAGE];
	float damageTime;           // last time any kind of damage was recieved
	int damageIndex;            // slot that was filled in
	float damageX, damageY, damageValue;
	float viewFade;

	int grenLastTime;

	int switchbackWeapon;
	int lastFiredWeapon;
	int lastWeapSelInBank[MAX_WEAP_BANKS];          // remember which weapon was last selected in a bank for 'weaponbank' commands //----(SA)	added
// JPW FIXME NOTE: max_weap_banks > max_weap_banks_mp so this should be OK, but if that changes, change this too

	// status bar head
	float headYaw;
	float headEndPitch;
	float headEndYaw;
	int headEndTime;
	float headStartPitch;
	float headStartYaw;
	int headStartTime;

	// view movement
	float v_dmg_time;
	float v_dmg_pitch;
	float v_dmg_roll;

	vec3_t kick_angles;         // weapon kicks
	vec3_t kick_origin;

	// RF, view flames when getting burnt
	int v_fireTime, v_noFireTime;
	vec3_t v_fireRiseDir;

	// temp working variables for player view
	float bobfracsin;
	int bobcycle;
	float xyspeed;
	int nextOrbitTime;

	// development tool
	refEntity_t testModelEntity;
	char testModelName[MAX_QPATH];
	qboolean testGun;

	// RF, new kick angles
	vec3_t kickAVel;            // for damage feedback, weapon recoil, etc
								// This is the angular velocity, to give a smooth
								// rotational feedback, rather than sudden jerks
	vec3_t kickAngles;          // for damage feedback, weapon recoil, etc
								// NOTE: this is not transmitted through MSG.C stream
								// since weapon kicks are client-side, and damage feedback
								// is rare enough that we can transmit that as an event
	float recoilPitch, recoilPitchAngle;

	// Duffy
	qboolean cameraMode;        // if rendering from a camera
	// Duffy end

	unsigned int cld;           // NERVE - SMF
	qboolean limboMenu;         // NERVE - SMF

	// NERVE - SMF - Objective info display
	int oidTeam;
	int oidPrintTime;
	int oidPrintCharWidth;
	int oidPrintY;
	char oidPrint[1024];
	int oidPrintLines;
	// -NERVE - SMF

	cameraShake_t cameraShake[MAX_CAMERA_SHAKE];
	float cameraShakePhase;
	vec3_t cameraShakeAngles;

	float rumbleScale;          //RUMBLE FX using new shakeCamera code

} cg_t;

typedef enum {
	HINT_NONE,      // reserved
	HINT_FORCENONE, // reserved
	HINT_PLAYER,
	HINT_ACTIVATE,
	HINT_NOACTIVATE,
	HINT_DOOR,
	HINT_DOOR_ROTATING,
	HINT_DOOR_LOCKED,
	HINT_DOOR_ROTATING_LOCKED,
	HINT_MG42,
	HINT_BREAKABLE,         // 10
	HINT_BREAKABLE_DYNAMITE,
	HINT_CHAIR,
	HINT_ALARM,
	HINT_HEALTH,
	HINT_TREASURE,
	HINT_KNIFE,
	HINT_LADDER,
	HINT_BUTTON,
	HINT_WATER,
	HINT_CAUTION,           // 20
	HINT_DANGER,
	HINT_SECRET,
	HINT_QUESTION,
	HINT_EXCLAMATION,
	HINT_CLIPBOARD,
	HINT_WEAPON,
	HINT_AMMO,
	HINT_ARMOR,
	HINT_POWERUP,
	HINT_HOLDABLE,          // 30
	HINT_INVENTORY,
	HINT_SCENARIC,
	HINT_EXIT,
	HINT_NOEXIT,
	HINT_EXIT_FAR,
	HINT_NOEXIT_FAR,
	HINT_PLYR_FRIEND,
	HINT_PLYR_NEUTRAL,
	HINT_PLYR_ENEMY,
	HINT_PLYR_UNKNOWN,      // 40
	HINT_BUILD,

	HINT_BAD_USER,  // invisible user with no target

	HINT_NUM_HINTS
} hintType_t;

typedef struct {
	qhandle_t charsetShader;
	// JOSEPH 4-17-00
	qhandle_t menucharsetShader;
	// END JOSEPH
	qhandle_t charsetProp;
	qhandle_t charsetPropGlow;
	qhandle_t charsetPropB;
	qhandle_t whiteShader;

	qhandle_t redFlagModel;
	qhandle_t blueFlagModel;

	qhandle_t armorModel;

	qhandle_t teamStatusBar;

	qhandle_t deferShader;

	// gib explosions
	qhandle_t gibAbdomen;
	qhandle_t gibArm;
	qhandle_t gibChest;
	qhandle_t gibFist;
	qhandle_t gibFoot;
	qhandle_t gibForearm;
	qhandle_t gibIntestine;
	qhandle_t gibLeg;
	qhandle_t gibSkull;
	qhandle_t gibBrain;

	// debris
	qhandle_t debBlock[6];
	qhandle_t debRock[3];
	qhandle_t debFabric[3];
	qhandle_t debWood[6];

	qhandle_t targetEffectExplosionShader;

	qhandle_t machinegunBrassModel;
	qhandle_t panzerfaustBrassModel;    //----(SA)	added

	// Rafael
	qhandle_t smallgunBrassModel;

	qhandle_t shotgunBrassModel;

	qhandle_t railRingsShader;
	qhandle_t railCoreShader;

	qhandle_t lightningShader;

	qhandle_t friendShader;

	//	qhandle_t	medicReviveShader;	//----(SA)	commented out from MP
	qhandle_t balloonShader;
	qhandle_t connectionShader;

	qhandle_t aiStateShaders[MAX_AISTATES];

	qhandle_t selectShader;
	qhandle_t viewBloodShader;
	qhandle_t tracerShader;
	qhandle_t crosshairShader[10];
	qhandle_t crosshairFriendly;    //----(SA)	added
	qhandle_t lagometerShader;
	qhandle_t backTileShader;
	qhandle_t noammoShader;

	qhandle_t reticleShader;
	//	qhandle_t	reticleShaderSimple;
	qhandle_t reticleShaderSimpleQ;
	//	qhandle_t	snooperShader;
	qhandle_t snooperShaderSimple;
	//	qhandle_t	binocShaderSimple;
	qhandle_t binocShaderSimpleQ;   // same as above, but quartered.  (trying to save texture space)

	qhandle_t smokePuffShader;
	qhandle_t smokePuffRageProShader;
	qhandle_t shotgunSmokePuffShader;
	qhandle_t waterBubbleShader;
	qhandle_t bloodTrailShader;

	qhandle_t nailPuffShader;

	//----(SA)	modified

		// cursor hints
		// would be nice to specify these in the menu scripts instead of permanent handles...
	qhandle_t hintShaders[HINT_NUM_HINTS];

	qhandle_t youGotMailShader;         // '!' - new entry in notebook
	qhandle_t youGotObjectiveShader;    // '<checkmark> - you completed objective
//----(SA)	end

	// Rafael
	qhandle_t snowShader;
	qhandle_t oilParticle;
	qhandle_t oilSlick;
	// done.

	// Rafael - cannon
	qhandle_t smokePuffShaderdirty;
	qhandle_t smokePuffShaderb1;
	qhandle_t smokePuffShaderb2;
	qhandle_t smokePuffShaderb3;
	qhandle_t smokePuffShaderb4;
	qhandle_t smokePuffShaderb5;
	// done

	// Rafael - blood pool
	qhandle_t bloodPool;

	// Ridah, viewscreen blood animation
	qhandle_t viewBloodAni[5];
	qhandle_t viewFlashBlood;
	qhandle_t viewFlashFire[16];
	// done

	// Rafael bats
	qhandle_t bats[10];
	// done

	// Rafael shards
	qhandle_t shardGlass1;
	qhandle_t shardGlass2;
	qhandle_t shardWood1;
	qhandle_t shardWood2;
	qhandle_t shardMetal1;
	qhandle_t shardMetal2;
	qhandle_t shardCeramic1;
	qhandle_t shardCeramic2;
	// done

	qhandle_t shardRubble1;
	qhandle_t shardRubble2;
	qhandle_t shardRubble3;


	qhandle_t shardJunk[5];

	qhandle_t numberShaders[11];

	qhandle_t shadowMarkShader;
	qhandle_t shadowFootShader;
	qhandle_t shadowTorsoShader;

	qhandle_t botSkillShaders[5];

	// wall mark shaders
	qhandle_t wakeMarkShader;
	qhandle_t wakeMarkShaderAnim;
	qhandle_t bloodMarkShaders[5];
	qhandle_t bloodDotShaders[5];
	qhandle_t bulletMarkShader;
	qhandle_t bulletMarkShaderMetal;
	qhandle_t bulletMarkShaderWood;
	qhandle_t bulletMarkShaderCeramic;
	qhandle_t bulletMarkShaderGlass;
	qhandle_t burnMarkShader;
	qhandle_t holeMarkShader;
	qhandle_t energyMarkShader;

	// powerup shaders
	qhandle_t quadShader;
	qhandle_t redQuadShader;
	qhandle_t quadWeaponShader;
	qhandle_t invisShader;
	qhandle_t regenShader;
	qhandle_t battleSuitShader;
	qhandle_t battleWeaponShader;
	qhandle_t hastePuffShader;

	// weapon effect models
	qhandle_t spearModel;   //----(SA)

	qhandle_t bulletFlashModel;
	qhandle_t ringFlashModel;
	qhandle_t dishFlashModel;
	qhandle_t lightningExplosionModel;

	qhandle_t zombieLoogie;
	qhandle_t flamebarrel;
	qhandle_t mg42muzzleflash;
	//qhandle_t	mg42muzzleflashgg;
	qhandle_t planemuzzleflash;

	// Rafael
	qhandle_t crowbar;

	qhandle_t waterSplashModel;
	qhandle_t waterSplashShader;

	qhandle_t thirdPersonBinocModel;    //----(SA)	added
	qhandle_t cigModel;     //----(SA)	added

	qhandle_t batModel;
	qhandle_t spiritSkullModel;
	qhandle_t helgaGhostModel;

	// weapon effect shaders
	qhandle_t railExplosionShader;
	qhandle_t bulletExplosionShader;
	qhandle_t rocketExplosionShader;
	qhandle_t grenadeExplosionShader;
	qhandle_t bfgExplosionShader;
	qhandle_t bloodExplosionShader;

	qhandle_t flameThrowerhitShader;

	// special effects models
	qhandle_t teleportEffectModel;
	qhandle_t teleportEffectShader;

	// scoreboard headers
	qhandle_t scoreboardName;
	qhandle_t scoreboardPing;
	qhandle_t scoreboardScore;
	qhandle_t scoreboardTime;
	// Ridah
	qhandle_t bloodCloudShader;
	qhandle_t sparkParticleShader;
	qhandle_t smokeTrailShader;
	qhandle_t fireTrailShader;
	qhandle_t lightningBoltShader;
	qhandle_t lightningBoltShaderGreen;
	qhandle_t flamethrowerFireStream;
	qhandle_t flamethrowerBlueStream;
	qhandle_t flamethrowerFuelStream;
	qhandle_t flamethrowerFuelShader;
	qhandle_t onFireShader, onFireShader2;
	//qhandle_t	dripWetShader, dripWetShader2;
	qhandle_t viewFadeBlack;
	qhandle_t sparkFlareShader;
	qhandle_t funnelFireShader[21];

	qhandle_t spotLightShader;
	qhandle_t spotLightBeamShader;
	qhandle_t spotLightBaseModel;       //----(SA)	added
	qhandle_t spotLightLightModel;      //----(SA)	added
	qhandle_t spotLightLightModelBroke;     //----(SA)	added

	qhandle_t lightningHitWallShader;
	qhandle_t lightningWaveShader;
	qhandle_t bulletParticleTrailShader;
	qhandle_t smokeParticleShader;

	// DHM - Nerve :: bullet hitting dirt
	qhandle_t dirtParticle1Shader;
	qhandle_t dirtParticle2Shader;
	qhandle_t dirtParticle3Shader;

	qhandle_t zombieSpiritWallShader;
	qhandle_t zombieSpiritTrailShader;
	qhandle_t zombieSpiritSkullShader;
	qhandle_t zombieDeathDustShader;
	qhandle_t zombieBodyFadeShader;
	qhandle_t zombieHeadFadeShader;

	qhandle_t helgaSpiritSkullShader;
	qhandle_t helgaSpiritTrailShader;

	qhandle_t ssSpiritSkullModel;

	qhandle_t skeletonSkinShader;
	qhandle_t skeletonLegsModel;
	qhandle_t skeletonTorsoModel;
	qhandle_t skeletonHeadModel;
	qhandle_t skeletonLegsSkin;
	qhandle_t skeletonTorsoSkin;
	qhandle_t skeletonHeadSkin;

	qhandle_t loperGroundChargeShader;

	qhandle_t teslaDamageEffectShader;
	qhandle_t teslaAltDamageEffectShader;
	qhandle_t viewTeslaDamageEffectShader;
	qhandle_t viewTeslaAltDamageEffectShader;
	// done.

//----(SA)
	// proto/super/heini armor parts
	qhandle_t protoArmor[9 * 3];        // 9 parts, 3 sections each	(nodam, dam1, dam2)
	qhandle_t superArmor[16 * 3];       // 14 parts, 3 sections each
	qhandle_t heinrichArmor[22 * 3];    // 20 parts, 3 sections each
//----(SA)	end

	// medals shown during gameplay
	qhandle_t medalImpressive;
	qhandle_t medalExcellent;
	qhandle_t medalGauntlet;

	// sounds
	sfxHandle_t n_health;
	sfxHandle_t noFireUnderwater;
	sfxHandle_t snipersound;
	sfxHandle_t quadSound;
	sfxHandle_t tracerSound;
	sfxHandle_t selectSound;
	sfxHandle_t useNothingSound;
	sfxHandle_t wearOffSound;
	sfxHandle_t footsteps[FOOTSTEP_TOTAL][4];
	sfxHandle_t sfx_lghit1;
	sfxHandle_t sfx_lghit2;
	sfxHandle_t sfx_lghit3;
	sfxHandle_t sfx_ric1;
	sfxHandle_t sfx_ric2;
	sfxHandle_t sfx_ric3;
	sfxHandle_t sfx_railg;
	sfxHandle_t sfx_rockexp;
	sfxHandle_t sfx_dynamiteexp;
	sfxHandle_t sfx_dynamiteexpDist;    //----(SA)	added
	sfxHandle_t sfx_spearhit;
	sfxHandle_t sfx_knifehit[5];
	sfxHandle_t sfx_bullet_metalhit[3];
	sfxHandle_t sfx_bullet_woodhit[3];
	sfxHandle_t sfx_bullet_roofhit[3];
	sfxHandle_t sfx_bullet_ceramichit[3];
	sfxHandle_t sfx_bullet_glasshit[3];
	sfxHandle_t gibSound;
	sfxHandle_t gibBounce1Sound;
	sfxHandle_t gibBounce2Sound;
	sfxHandle_t gibBounce3Sound;
	sfxHandle_t teleInSound;
	sfxHandle_t teleOutSound;
	sfxHandle_t noAmmoSound;
	sfxHandle_t respawnSound;
	sfxHandle_t talkSound;
	sfxHandle_t landSound;
	sfxHandle_t fallSound;
	sfxHandle_t jumpPadSound;

	sfxHandle_t oneMinuteSound;
	sfxHandle_t fiveMinuteSound;
	sfxHandle_t suddenDeathSound;

	sfxHandle_t threeFragSound;
	sfxHandle_t twoFragSound;
	sfxHandle_t oneFragSound;

	sfxHandle_t hitSound;
	sfxHandle_t hitTeamSound;
	sfxHandle_t impressiveSound;
	sfxHandle_t excellentSound;
	sfxHandle_t deniedSound;
	sfxHandle_t humiliationSound;

	sfxHandle_t takenLeadSound;
	sfxHandle_t tiedLeadSound;
	sfxHandle_t lostLeadSound;

	sfxHandle_t watrInSound;
	sfxHandle_t watrOutSound;
	sfxHandle_t watrUnSound;

	//	sfxHandle_t flightSound;
	sfxHandle_t underWaterSound;
	sfxHandle_t medkitSound;
	sfxHandle_t wineSound;
	sfxHandle_t bookSound;      //----(SA)	added
	sfxHandle_t staminaSound;   //----(SA)	added
	sfxHandle_t elecSound;
	sfxHandle_t fireSound;
	sfxHandle_t waterSound;

	// teamplay sounds
	sfxHandle_t redLeadsSound;
	sfxHandle_t blueLeadsSound;
	sfxHandle_t teamsTiedSound;

	// tournament sounds
	sfxHandle_t count3Sound;
	sfxHandle_t count2Sound;
	sfxHandle_t count1Sound;
	sfxHandle_t countFightSound;
	sfxHandle_t countPrepareSound;

	//----(SA) added
	sfxHandle_t debBounce1Sound;
	sfxHandle_t debBounce2Sound;
	sfxHandle_t debBounce3Sound;
	//----(SA) end

	//----(SA)	added
	sfxHandle_t grenadePulseSound4;
	sfxHandle_t grenadePulseSound3;
	sfxHandle_t grenadePulseSound2;
	sfxHandle_t grenadePulseSound1;
	//----(SA)

//----(SA)	added
	sfxHandle_t sparkSounds[2];
	//----(SA)

		// Ridah
	sfxHandle_t flameSound;
	sfxHandle_t flameBlowSound;
	sfxHandle_t flameStartSound;
	sfxHandle_t flameStreamSound;
	sfxHandle_t lightningSounds[3];
	sfxHandle_t lightningZap;
	sfxHandle_t flameCrackSound;
	sfxHandle_t boneBounceSound;

	sfxHandle_t zombieSpiritSound;
	sfxHandle_t zombieSpiritLoopSound;
	sfxHandle_t zombieDeathSound;

	sfxHandle_t helgaSpiritLoopSound;
	sfxHandle_t helgaSpiritSound;
	sfxHandle_t helgaGaspSound;

	sfxHandle_t heinrichArmorBreak; //----(SA)
	sfxHandle_t protoArmorBreak;    //----(SA)
	sfxHandle_t superArmorBreak;    //----(SA)


	sfxHandle_t debrisHitSound;

	sfxHandle_t loperLightningSounds[3];
	sfxHandle_t loperLightningZap;

	sfxHandle_t lightningClap[5];

	sfxHandle_t batsFlyingLoopSound;

	//	sfxHandle_t grenadebounce1;
	//	sfxHandle_t grenadebounce2;
	sfxHandle_t grenadebounce[4][2]; //----(SA)	modified

	sfxHandle_t dynamitebounce1;    //----(SA)	added

	sfxHandle_t fbarrelexp1;
	sfxHandle_t fbarrelexp2;

	sfxHandle_t fkickwall;
	sfxHandle_t fkickflesh;
	sfxHandle_t fkickmiss;

	int bulletHitFleshScript;
	int bulletHitFleshMetalScript;

	int teslaZapScript;
	sfxHandle_t teslaLoopSound;
	// done.

	qhandle_t cursor;
	qhandle_t selectCursor;
	qhandle_t sizeCursor;

} cgMedia_t;

typedef enum {
	GT_FFA,             // free for all
	GT_TOURNAMENT,      // one on one tournament
	GT_SINGLE_PLAYER,   // single player tournament

	//-- team games go after this --

	GT_TEAM,            // team deathmatch
	GT_CTF,             // capture the flag
	GT_WOLF,            // DHM - Nerve :: Wolfenstein Multiplayer

	GT_MAX_GAME_TYPE
} gametype_t;

// Rafael gameskill
typedef enum {
	GSKILL_EASY,
	GSKILL_MEDIUM,
	GSKILL_HARD,
	GSKILL_MAX      // must always be last
} gameskill_t;

#define TEAMCHAT_WIDTH      80
#define TEAMCHAT_HEIGHT     8

#define MAX_ITEMS           256

// The client game static (cgs) structure hold everything
// loaded or calculated from the gamestate.  It will NOT
// be cleared when a tournement restart is done, allowing
// all clients to begin playing instantly
typedef struct {
	gameState_t gameState;              // gamestate from server
	glconfig_t glconfig;                // rendering configuration
	float screenXScale;                 // derived from glconfig
	float screenYScale;
	float screenXBias;

	int serverCommandSequence;              // reliable command stream counter
	int processedSnapshotNum;            // the number of snapshots cgame has requested

	qboolean localServer;               // detected on startup by checking sv_running

	// parsed from serverinfo
	gametype_t gametype;

	// Rafael gameskill
	gameskill_t gameskill;
	// done

	int dmflags;
	int teamflags;
	int fraglimit;
	int capturelimit;
	int timelimit;
	int maxclients;
	char mapname[MAX_QPATH];
	char redTeam[MAX_QPATH];                // A team
	char blueTeam[MAX_QPATH];               // B team

	int voteTime;
	int voteYes;
	int voteNo;
	qboolean voteModified;                  // beep whenever changed
	char voteString[MAX_STRING_TOKENS];

	int teamVoteTime[2];
	int teamVoteYes[2];
	int teamVoteNo[2];
	qboolean teamVoteModified[2];           // beep whenever changed
	char teamVoteString[2][MAX_STRING_TOKENS];

	int levelStartTime;

	int scores1, scores2;                   // from configstrings

	//
	// locally derived information from gamestate
	//
	qhandle_t gameModels[MAX_MODELS];

	sfxHandle_t gameSounds[MAX_SOUNDS];
	int gameSoundTypes[MAX_SOUNDS];             //----(SA)	added

	int numInlineModels;
	qhandle_t inlineDrawModel[MAX_MODELS];
	vec3_t inlineModelMidpoints[MAX_MODELS];

	clientInfo_t clientinfo[MAX_CLIENTS];

	// teamchat width is *3 because of embedded color codes
	char teamChatMsgs[TEAMCHAT_HEIGHT][TEAMCHAT_WIDTH * 3 + 1];
	int teamChatMsgTimes[TEAMCHAT_HEIGHT];
	int teamChatPos;
	int teamLastChatPos;

	char itemPrintNames[MAX_ITEMS][32];             //----(SA)	added

	int cursorX;
	int cursorY;
	qboolean eventHandling;
	qboolean mouseCaptured;
	qboolean sizingHud;
	void *capturedItem;
	qhandle_t activeCursor;

	// screen fading
	//----(SA)	modified just in name so global searching is easier to narrow down (added 'scrF')
	float scrFadeAlpha, scrFadeAlphaCurrent;
	int scrFadeStartTime;
	int scrFadeDuration;

	// media
	cgMedia_t media;

	// player/AI model scripting (client repository)
	animScriptData_t animScriptData;

} cgs_t;

/*
==============================================================================

MDS file format(Wolfenstein Skeletal Format)

==============================================================================
*/

#define MDS_IDENT           ( ( 'W' << 24 ) + ( 'S' << 16 ) + ( 'D' << 8 ) + 'M' )
#define MDS_VERSION         4
#define MDS_MAX_VERTS       6000
#define MDS_MAX_TRIANGLES   8192
#define MDS_MAX_BONES       128
#define MDS_MAX_SURFACES    32
#define MDS_MAX_TAGS        128

#define MDS_TRANSLATION_SCALE   ( 1.0 / 64 )

typedef struct {
	int boneIndex;              // these are indexes into the boneReferences,
	float boneWeight;           // not the global per-frame bone list
	vec3_t offset;
} mdsWeight_t;

typedef struct {
	vec3_t normal;
	vec2_t texCoords;
	int numWeights;
	int fixedParent;            // stay equi-distant from this parent
	float fixedDist;
	mdsWeight_t weights[1];     // variable sized
} mdsVertex_t;

typedef struct {
	int indexes[3];
} mdsTriangle_t;

typedef struct {
	int ident;

	char name[MAX_QPATH];           // polyset name
	char shader[MAX_QPATH];
	int shaderIndex;                // for in-game use

	int minLod;

	int ofsHeader;                  // this will be a negative number

	int numVerts;
	int ofsVerts;

	int numTriangles;
	int ofsTriangles;

	int ofsCollapseMap;           // numVerts * int

	// Bone references are a set of ints representing all the bones
	// present in any vertex weights for this surface.  This is
	// needed because a model may have surfaces that need to be
	// drawn at different sort times, and we don't want to have
	// to re-interpolate all the bones for each surface.
	int numBoneReferences;
	int ofsBoneReferences;

	int ofsEnd;                     // next surface follows
} mdsSurface_t;

typedef struct {
	//float		angles[3];
	//float		ofsAngles[2];
	short angles[4];            // to be converted to axis at run-time (this is also better for lerping)
	short ofsAngles[2];         // PITCH/YAW, head in this direction from parent to go to the offset position
} mdsBoneFrameCompressed_t;

// NOTE: this only used at run-time
typedef struct {
	float matrix[3][3];             // 3x3 rotation
	vec3_t translation;             // translation vector
} mdsBoneFrame_t;

typedef struct {
	vec3_t bounds[2];               // bounds of all surfaces of all LOD's for this frame
	vec3_t localOrigin;             // midpoint of bounds, used for sphere cull
	float radius;                   // dist from localOrigin to corner
	vec3_t parentOffset;            // one bone is an ascendant of all other bones, it starts the hierachy at this position
	mdsBoneFrameCompressed_t bones[1];              // [numBones]
} mdsFrame_t;

typedef struct {
	int numSurfaces;
	int ofsSurfaces;                // first surface, others follow
	int ofsEnd;                     // next lod follows
} mdsLOD_t;

typedef struct {
	char name[MAX_QPATH];           // name of tag
	float torsoWeight;
	int boneIndex;                  // our index in the bones
} mdsTag_t;

#define BONEFLAG_TAG        1       // this bone is actually a tag

typedef struct {
	char name[MAX_QPATH];           // name of bone
	int parent;                     // not sure if this is required, no harm throwing it in
	float torsoWeight;              // scale torso rotation about torsoParent by this
	float parentDist;
	int flags;
} mdsBoneInfo_t;

typedef struct {
	int ident;
	int version;

	char name[MAX_QPATH];           // model name

	float lodScale;
	float lodBias;

	// frames and bones are shared by all levels of detail
	int numFrames;
	int numBones;
	int ofsFrames;                  // md4Frame_t[numFrames]
	int ofsBones;                   // mdsBoneInfo_t[numBones]
	int torsoParent;                // index of bone that is the parent of the torso

	int numSurfaces;
	int ofsSurfaces;

	// tag data
	int numTags;
	int ofsTags;                    // mdsTag_t[numTags]

	int ofsEnd;                     // end of file
} mdsHeader_t;

typedef struct {
	int commandId;
	float color[4];
} setColorCommand_t;