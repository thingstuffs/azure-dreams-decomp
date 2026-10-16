#ifndef MODULE_DUNGEON_OVL_E0365C_H
#define MODULE_DUNGEON_OVL_E0365C_H
#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "records/Rec_D_80082E80.h"
#include "m2c_compat.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_func_80173204_arg0.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef void (*E_80170854_ActorAction)(void *,void *,void *,void *);
typedef struct {
 u8 pad00[0x13]; u8 kind; s32 flags14; u8 pad18[4]; s32 flags1C;
 u8 pad20[0x6C]; E_80170854_ActorAction handler;
} E_80170854_SpawnActor;
typedef struct {
 u8 pad00[0x8C]; E_80170854_ActorAction handler; u8 pad90[0xA]; u8 action_id;
 u8 pad9B; s8 direction;
} E_80170854_SpawnState;
typedef struct { u8 pad00[0xA]; s16 height; } E_80170854_SpawnMotion;
typedef struct { u8 pad00[0x24]; u8 tile_x,tile_y; u8 pad26[6]; u8 *frames; } E_80170854_SpawnSprite;
typedef struct { u8 pad00[8]; E_80170854_SpawnMotion *motion; E_80170854_SpawnSprite *sprite; void (*update)(void *,void *,void *); } E_80170854_SpawnObject;










extern u8 D_80174510[8],D_80174538[8];
/* Allocate an actor, initialize its action and sprite views, then apply spawn flags. */

typedef void (*E_80170A58_Callback)(void *, void *, void *, void *);













typedef struct E_80170A58_S_80170A58_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} E_80170A58_S_80170A58_0;   /* monster in func_80170A58 */

typedef struct E_80170A58_S_80170A58_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4D];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} E_80170A58_S_80170A58_1;   /* actor in func_80170A58 */

typedef struct E_80170A58_S_80170A58_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80170A58_S_80170A58_2;   /* motion in func_80170A58 */

/* Updates monster facing, runs actor callbacks, and applies motion and floor contact. */

typedef struct E_80170E5C_S_80170E5C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} E_80170E5C_S_80170E5C_0;   /* arg0 in func_80170E5C */

typedef struct E_80170E5C_S_80170E5C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} E_80170E5C_S_80170E5C_1;   /* arg3 in func_80170E5C */

typedef struct E_80170E5C_S_80170E5C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} E_80170E5C_S_80170E5C_2;   /* arg2 in func_80170E5C */
































/* Update actor actions, facing, and animation according to dungeon state. */

/* Updates actor movement, recording the path and refreshing the tile position and height. */

typedef struct E_80171B68_S_80171570_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} E_80171B68_S_80171570_0;   /* state in func_80171B68 */


typedef struct E_80171B68_S_80171570_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} E_80171B68_S_80171570_2;   /* arg0 in func_80171B68 */

typedef struct E_80171B68_S_80171570_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} E_80171B68_S_80171570_3;   /* (u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A in func_80171B68 */











/* Advances the entity along its stored path and updates movement timing. */

// Initialize object state and apply the table entry for its eight-way orientation.

typedef struct E_80171E10_S_80171E00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} E_80171E10_S_80171E00_3;   /* arg0 in func_80171E10 */


         /* extern */
typedef struct E_80171E10_Ent E_80171E10_Ent;
 /* extern */
                     /* extern */
             /* extern */
                          /* extern */
                     /* extern */
 /* extern */


/* Check movement conditions and initialize the actor action and directional animation. */

typedef struct E_80171FD4_S_80171FC4_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} E_80171FD4_S_80171FC4_1;   /* arg0 in func_80171FD4 */


         /* extern */
typedef struct E_80171FD4_Ent E_80171FD4_Ent;
 /* extern */
                          /* extern */
 /* extern */


/* Update action state and start a directional animation if the actor passes the checks. */

typedef struct E_801720EC_S_801720EC_0 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    union { s16 s; u16 u; } unk_88;   /* accessed as both */
} E_801720EC_S_801720EC_0;   /* entity in func_801720EC */

typedef struct E_801720EC_S_801720EC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} E_801720EC_S_801720EC_1;   /* arg2 in func_801720EC */

typedef struct E_801720EC_S_801720EC_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} E_801720EC_S_801720EC_2;   /* output in func_801720EC */














/* Checks the tile ahead and updates the entity's action when the height permits. */

typedef struct E_8017236C_S_8017236C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} E_8017236C_S_8017236C_1;   /* arg0 in func_8017236C */








/* Updates actor flags and starts a directional animation when the actor is ready. */

typedef void (*E_8017246C_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_8017246C_ActorAction handler; s32 timer; } E_8017246C_ActionState;

typedef struct E_801724E8_S_801724E8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} E_801724E8_S_801724E8_0;   /* arg0 in func_801724E8 */













/* Updates an actor's hop toward its tile and handles movement completion. */

typedef void (*E_80172850_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_80172850_ActorAction handler; s32 timer; } E_80172850_ActionState;

typedef struct E_801728B4_S_801728B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_801728B4_S_801728B4_0;   /* obj in func_801728B4 */

typedef struct E_801728B4_S_801728B4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} E_801728B4_S_801728B4_1;   /* entity in func_801728B4 */

typedef struct E_801728B4_S_801728B4_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} E_801728B4_S_801728B4_2;   /* actor in func_801728B4 */


 /* extern */
                      /* extern */
                     /* extern */
             /* extern */
/* Advances the object state from entity flags and updates the actor. */

/* extern */
         /* extern */
      /* extern */
              /* extern */
                      /* extern */
                     /* extern */
       /* extern */
                      /* extern */






typedef struct E_80172A58_S_80172A58_0 {
    u8 pad_00[0x8C];
    void (*unk_8C)(void *,void *,void *,void *);
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} E_80172A58_S_80172A58_0;   /* arg0 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    s8 unk_72;
    s8 unk_73;
} E_80172A58_S_80172A58_1;   /* arg3 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_2 {
    u8 pad_00[0x12];
    u8 unk_12;
} E_80172A58_S_80172A58_2;   /* ((*var_s0 * 0x14) + D_8006DE24) in func_80172A58 */

typedef struct E_80172A58_S_80172A58_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} E_80172A58_S_80172A58_3_pre;   /* the 0x14 bytes before var_v0 in func_80172A58, addressed as var_v0[-1] */

typedef struct E_80172A58_S_80172A58_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} E_80172A58_S_80172A58_4;   /* temp_v1_3 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} E_80172A58_S_80172A58_5;   /* arg2 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80172A58_S_80172A58_6;   /* arg1 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_7 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} E_80172A58_S_80172A58_7;   /* D_800814A8 in func_80172A58 */

typedef struct E_80172A58_S_80172A58_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} E_80172A58_S_80172A58_8;   /* &D_80083460 in func_80172A58 */

typedef struct E_80172ED0_S_80172ED0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} E_80172ED0_S_80172ED0_0;   /* arg0 in func_80172ED0 */









/* Damp entity movement and align it to its tile before starting an action or resetting state. */





/* Forward all four bank callback arguments to the resident handler. */

typedef void (*E_8017321C_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_8017321C_ActorAction handler; s32 timer; } E_8017321C_ActionState;


/* Resume the bank action after the resident callback completes. */

typedef struct E_80173254_S_80173254_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_80173254_S_80173254_0;   /* arg0 in func_80173254 */


/* Updates the entity action state and selects its directional animation. */

typedef struct E_8017357C_S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_8017357C_S_8017357C_0;   /* arg0 in func_8017357C */
















/* Advance the actor state and select its directional effect. */

typedef void (*E_801737DC_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_801737DC_ActorAction handler; s32 timer; } E_801737DC_ActionState;

typedef struct {u8 pad00[0x2C];u8 *frames;} E_801737DC_RenderState;
typedef struct {u8 pad00[0x1C];s32 flags;u8 pad20[0xA];s16 facing;} E_801737DC_RenderActor;




extern u8 D_80174518[8],D_80174538[8];

typedef void (*E_801738A4_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_801738A4_ActorAction handler; s32 timer; } E_801738A4_ActionState;

typedef void (*E_80173908_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_80173908_ActorAction handler; s32 timer; } E_80173908_ActionState;


/* Resume the bank action after the resident callback completes. */

typedef void (*E_80173940_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_80173940_ActorAction handler; s32 timer; } E_80173940_ActionState;


/* Resume the bank action after the resident callback completes. */

typedef void (*E_80173978_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_80173978_ActorAction handler; s32 timer; } E_80173978_ActionState;


/* Resume the bank action after the resident callback completes. */

typedef void (*E_801739B0_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_801739B0_ActorAction handler; s32 timer; } E_801739B0_ActionState;


/* Resume the bank action after the resident callback completes. */

typedef void (*E_801739E8_ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; E_801739E8_ActorAction handler; s32 timer; } E_801739E8_ActionState;


/* Resume the bank action after the resident callback completes. */

typedef struct E_80173A20_S_80173A20_2 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} E_80173A20_S_80173A20_2;   /* shadow in func_80173A20 */

typedef struct E_80173A20_S_80173A20_3 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0xA];
    u32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    union { u16 s; s16 u; } unk_88;   /* accessed as both */
} E_80173A20_S_80173A20_3;   /* creature in func_80173A20 */

typedef struct E_80173A20_S_80173A20_4 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 unk_29;
} E_80173A20_S_80173A20_4;   /* object in func_80173A20 */













/* Advance the actor state and spawn an adjacent object when entity flags allow. */

typedef struct E_80173CE0_S_80173CE0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} E_80173CE0_S_80173CE0_0;   /* arg0 in func_80173CE0 */

typedef struct E_80173CE0_S_80173CE0_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} E_80173CE0_S_80173CE0_1;   /* arg2 in func_80173CE0 */







/* Advance the action state and update the entity when action flags permit. */

/* extern */
                      /* extern */
 /* extern */
 /* extern */

typedef struct E_80173E48_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} E_80173E48_S_80172628_0;   /* hold_arg0 in func_80173E48 */

/* Update entity state and flags according to the state query result. */

typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1c;
    u16 field1e;
} E_80173F8C_Func80DE678C_Obj;

/* Update object motion unless its flags trigger termination. */

typedef s32 E_80174084_M2C_UNK;

typedef struct E_80174084_S_80DE6884_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} E_80174084_S_80DE6884_0;   /* setup_arg1 in func_80174084 */

typedef struct E_80174084_S_80DE6884_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    E_80174084_M2C_UNK * unk_10;
} E_80174084_S_80DE6884_1;   /* temp_v0 in func_80174084 */

typedef struct E_80174084_S_80DE6884_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} E_80174084_S_80DE6884_2;   /* temp_s0 in func_80174084 */

typedef struct E_80174084_S_80DE6884_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80174084_S_80DE6884_3;   /* held_arg1 in func_80174084 */

typedef struct E_80174084_S_80DE6884_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} E_80174084_S_80DE6884_4;   /* temp_s0_2 in func_80174084 */

typedef struct E_80174084_S_80DE6884_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} E_80174084_S_80DE6884_5;   /* held_arg0 in func_80174084 */

typedef struct {
    s32 words[6];
} E_80174084_Copy24;
#define NULL 0









static __inline__ u16 offset_coord(u16 coord, u16 offset) {
    return coord + offset;
}

static __inline__ u16 set_flags(u16 value, u16 flags) {
    return value | flags;
}

/* Spawns four effects with origin offsets, random rotation, and velocity based on the owner heading. */

/* extern */


/* Advances the counter, increments both fields for the first eight steps, and updates the record. */

typedef s32 E_801742AC_M2C_UNK;


#define NULL 0






typedef struct {
    s32 words[6];
} E_801742AC_Copy24;

typedef struct E_801742AC_S_80DE6AAC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    E_801742AC_M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} E_801742AC_S_80DE6AAC_0;   /* temp_v0 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} E_801742AC_S_80DE6AAC_1;   /* temp_s1 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} E_801742AC_S_80DE6AAC_2;   /* arg0 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} E_801742AC_S_80DE6AAC_3;   /* temp_s0 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} E_801742AC_S_80DE6AAC_4;   /* arg2 in func_801742AC */

typedef struct E_801742AC_S_80DE6AAC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
} E_801742AC_S_80DE6AAC_5;   /* temp_s0_2 in func_801742AC */

/* Creates an effect at a directional tile offset and clamps its height. */

/* Build an encoded message from the record and this bank's suffix. */

/* Build an encoded message from the record and this bank's suffix. */
extern s16 D_8006CD00[8];
extern u8 D_8006DE24[];
extern E_80174084_M2C_UNK D_800DEA68[3];
extern E_801742AC_M2C_UNK D_800DEEC0;
extern u8 D_80174518[];
extern u8 D_80174520[];
extern u8 D_80174528[8];
extern u8 D_80174530[];
extern u8 D_80174538[];
extern u8 D_80174540;
extern u8 D_80174548[];
extern s32 D_80174550;
extern u8 D_80174558[];
extern u8 D_80174560[];
extern E_80170A58_Callback D_80174568[];
extern u8 D_801745CC[];
extern u8 D_801745F8[];
extern int abs(int);
extern E_80174084_M2C_UNK func_8003DB94();
extern s32 func_8003DE58(s32, void *, s16 *, s32);
extern s32 func_8003F270(void);
extern void *func_8003FD64(s32,void *);
extern void func_80042640(void *, s32);
extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_8004491C(void *,void *);
extern void func_80047738();
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *arg);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u8 *func_800990FC(void);
extern u8 *func_80099194(u8 *,u8 *);
extern void *func_80099290(s8 *);
extern u8 *func_80099734(void *,u8 *);
extern s32 func_8009A180(void *, void *);
extern void func_8009A21C(s16 x, s16 y, u16 flags);
extern void func_8009A3D0(s32, s32, s32);
extern s32 func_8009A540();
extern s16 func_8009A66C(s16,void *,void *,s32);
extern s32 func_8009B4B0();
extern void * func_8009C12C();
extern E_80171E10_Ent * func_8009C93C();
extern s32 func_8009FB34(s32, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_8009FD7C(s32, s32, s32, s32);
/* Signed differences arrive sign-extended in the 32-bit v0 ABI slot.
 * The two signed comparisons explicitly narrow that slot; the other caller
 * performs modulo-16-bit arithmetic. One whole-bank declaration is used. */
extern s32 func_800A0134(void *,void *);
extern void func_800A020C();
extern void * func_800A02AC();
extern void * func_800A04F0();
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void func_800A0E6C();
extern void func_800A19E4();
extern s32 func_800A1C58(void *);
extern void func_800A2B04(void *, s32, s32);
extern s32 func_800A2B5C();
extern s32 func_800A2BDC();
extern s32 func_800A2C34(void *);
extern s32 func_800A2CB8();
extern s32 func_800A44E0();
extern void func_800A48F0(void *,s32,s32);
extern s32 func_800A4ACC(void *record);
extern s32 func_800A5690();
extern M2C_UNK func_800A56E0(M2C_UNK);
extern s32 func_800A5720(s8 *);
extern s32 func_800A6D30(void);
extern s32 func_800A94A0(void *, u8 *, s32, void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800A9C18(void *,void *,void *,s16);
extern s32 func_800A9E70();
extern void func_800AA258(void *, void *, void *, void *);
extern void func_800AA36C(void *,void *,void *,void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAA54();
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern s32 func_800AB1C0(void *,void *,void *,void *);
extern s32 func_800AB378(void *,void *,void *,void *);
extern s32 func_800AB464(void *,void *,void *,void *);
extern s32 func_800AB538(void *,void *,void *,void *);
extern s32 func_800AB778(void *, s32, void *, void *);
extern s32 func_800ABDBC(void *,void *,void *,void *);
extern s32 func_800AC010(void *,void *,void *,void *);
extern s32 func_800AC480(void *,void *,void *,void *);
extern s32 func_800AC5C8(void *,void *,void *,void *);
extern s32 func_800AC7EC(void *,void *,void *,void *);
extern s32 func_800AC82C(void *,void *,void *,void *);
extern s32 func_800ACE34(void *,void *,void *,void *);
extern void func_800AD058(void *,void *,void *,void *);
extern void func_800AD4D0();
extern void func_800AD594(void *,s32);
extern s32 func_800AD9B4(void *,void *);
extern s32 func_800ADDA0();
extern M2C_UNK func_800BB044(void *);
extern s16 func_800BCB04(s32,s32,s16);
extern s32 func_800C77D0(s32 slot_id, void *target, s32 target_id, s16 slot_value);
extern s32 func_800C7930(s32 object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
extern void *func_800D3F74(s32, s16, s16, s16);
extern s32 rand();

void *func_80170854(s16 flags,s16 attr_x,s16 attr_y,s16 attr_height);
void func_80170A58(void *entity, E_80170A58_S_80170A58_2 *motion, void *monster);
void func_80170E5C(void *actor_in, void *context_in, void *sprite_in, void *status_in);
void func_80171420(u8 *object, void *entry_context, u8 *tile, u8 *actor);
void func_80171B68(void *action, s32 action_id, void *entity, void *move_state);
void func_80171DAC(void *object, void *unused, void *display, void *orientation);
s32 func_80171E10(void *action_state, void *action_ctx, void *sprite, EntityRec *actor);
void func_80171FD4(void *action_state, void *action_context, void *sprite, EntityRec *actor);
s32 func_801720EC(void *action_state, void *source_pos, void *sprite, void *actor);
void func_8017236C(void *actor_state, s32 action_param, void *sprite, EntityRec *actor);
void func_8017246C(E_8017246C_ActionState *state,void *motion,void *sprite,void *actor);
void func_801724E8(void *anim, EntityRec *motion, void *actor, EntityRec *actor_state);
void func_80172850(E_80172850_ActionState *state,void *motion,void *sprite,void *actor);
void func_801728B4(void *obj, EntityRec *record, void *entity, void *actor);
void func_80172A58(void *arg0, E_80172A58_S_80172A58_6 *arg1, E_80172A58_S_80172A58_5 *arg2, void *arg3);
void func_80172ED0(E_80172ED0_S_80172ED0_0 *action, EntityRec *motion, Rec_D_80082E80 *tile_state, void *entity);
void func_801731BC(void *state,void *position,void *render_state,void *entity);
void func_801731DC(void *state,void *motion,void *sprite,void *actor);
void func_801731FC(void *state, s32 action, SpriteFrameState *source, EntityRec *target);
void func_8017321C(E_8017321C_ActionState *state,void *motion,void *sprite,void *actor);
void func_80173254(void *action, void *context, void *sprite, EntityRec *entity);
void func_8017357C(void *controller, void *context, void *sprite, EntityRec *actor);
void func_801737DC(E_801737DC_ActionState *state,void *motion,E_801737DC_RenderState *sprite,E_801737DC_RenderActor *actor);
void func_801738A4(E_801738A4_ActionState *state,void *motion,void *sprite,void *actor);
void func_80173908(E_80173908_ActionState *state,void *motion,void *sprite,void *actor);
void func_80173940(E_80173940_ActionState *state,void *motion,void *sprite,void *actor);
void func_80173978(E_80173978_ActionState *state,void *motion,void *sprite,void *actor);
void func_801739B0(E_801739B0_ActionState *state,void *motion,void *sprite,void *actor);
void func_801739E8(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor);
void func_80173A20(void *actor, void *context, void *entity, void *creature);
void func_80173CE0(void *state_ctx, s32 entity_id, void *action, void *entity);
s32 func_80173E48(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_80173F8C(void *state_data, s32 *motion, E_80173F8C_Func80DE678C_Obj *object);
void func_80174084(void *owner_arg, void *motion_arg, void *origin_arg);
void func_80174254(u16 *counter, M2C_UNK unused, Rec_D_80082E80 *record);
s32 func_801742AC(E_801742AC_S_80DE6AAC_2 *source, void *initial_position, E_801742AC_S_80DE6AAC_4 *tile_origin);
void func_80174460(void *record);
void func_801744B8(void *record);
#endif
