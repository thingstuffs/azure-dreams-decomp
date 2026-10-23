#ifndef MODULE_DUNGEON_OVL_CB9000_H
#define MODULE_DUNGEON_OVL_CB9000_H


struct ObjectPosition;
struct SpriteFrameState;
#include "common.h"
#include "dungeon/modules.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/tile_object.h"
#include "m2c_compat.h"
#include "shared/dungeon_floor.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/def_table.h"
#include "records/Rec_func_80173CFC_arg1.h"

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} CL_CB9000_8017087C_CopyFields;

typedef struct {
    u8 pad0[0xC];
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 field14;
    u8 pad16[6];
    s16 field1C;
    s16 field1E;
} CL_CB9000_8017087C_Part;

typedef struct {
    u8 pad0[8];
    CL_CB9000_8017087C_CopyFields *copy;
    CL_CB9000_8017087C_Part *part;
    u8 pad10[0x50];
    s32 field60;
} CL_CB9000_8017087C_Object;

typedef struct CL_CB9000_80170920_S_80170920_0 {
    u8 pad_00[0x1C];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x6];
    union { u16 s; s16 u; } unk_24;   /* accessed as both */
    s16 unk_26;
} CL_CB9000_80170920_S_80170920_0;   /* arg0 in func_8016A920 */

typedef struct CL_CB9000_80170920_S_80170920_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x8];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} CL_CB9000_80170920_S_80170920_1;   /* arg2 in func_8016A920 */

/* Expands and brightens the effect, then shrinks and fades it until expiration. */

typedef struct CL_CB9000_80170A5C_S_80170A5C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} CL_CB9000_80170A5C_S_80170A5C_1;   /* result in func_8016AA5C */

typedef struct CL_CB9000_80170A5C_S_80170A5C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} CL_CB9000_80170A5C_S_80170A5C_2;   /* part0 in func_8016AA5C */

typedef struct CL_CB9000_80170A5C_S_80170A5C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} CL_CB9000_80170A5C_S_80170A5C_4;   /* result_copy in func_8016AA5C */

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */

typedef void (*CL_CB9000_80170C24_Callback)(void *, void *, void *, void *);

typedef struct CL_CB9000_80170C24_S_80170C24_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} CL_CB9000_80170C24_S_80170C24_0;   /* monster in func_8016AC24 */

typedef struct CL_CB9000_80170C24_S_80170C24_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    union { u16 u; s16 s; } unk_88;   /* accessed as both */
} CL_CB9000_80170C24_S_80170C24_1;   /* actor in func_8016AC24 */

typedef struct CL_CB9000_80170C24_S_80170C24_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} CL_CB9000_80170C24_S_80170C24_2;   /* motion in func_8016AC24 */

/* Runs entity callbacks, updates monster facing, and applies motion and floor collision. */

/* extern */
                     /* extern */
                           /* extern */
                  /* extern */
       /* extern */
                          /* extern */
                      /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
                            /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */
 /* extern */

typedef struct CL_CB9000_8017102C_S_8017102C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
} CL_CB9000_8017102C_S_8017102C_0;   /* arg0 in func_8016B02C */

typedef struct CL_CB9000_8017102C_S_8017102C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} CL_CB9000_8017102C_S_8017102C_1;   /* arg3 in func_8016B02C */

typedef struct CL_CB9000_8017102C_S_8017102C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 x; u8 y; } bytes; u16 packed; } tile;
    s8 unk_26;
    u8 pad_27[0x5];
    u8 *unk_2C;
} CL_CB9000_8017102C_S_8017102C_2;   /* arg2 in func_8016B02C */

typedef struct CL_CB9000_8017102C_S_8017102C_3 {
    u8 pad_00[0x58];
    s32 unk_58;
    u8 pad_5C[0x3E];
    u8 unk_9A;
} CL_CB9000_8017102C_S_8017102C_3;   /* D_800814A8 in func_8016B02C */

typedef struct CL_CB9000_8017102C_S_8017102C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} CL_CB9000_8017102C_S_8017102C_4;   /* &D_80082E80 in func_8016B02C */

typedef struct CL_CB9000_8017102C_S_8017102C_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
} CL_CB9000_8017102C_S_8017102C_5;   /* ((temp_v0 * 0x14) + &D_800E2970) in func_8016B02C */

/* Advance the action dispatcher and select the actor's next movement or animation state. */

typedef struct CL_CB9000_80171590_S_80171590_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} CL_CB9000_80171590_S_80171590_0;   /* state in func_8016B590 */

typedef struct CL_CB9000_80171590_S_80171590_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} CL_CB9000_80171590_S_80171590_1;   /* arg2 in func_8016B590 */

typedef struct CL_CB9000_80171590_S_80171590_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x9];
    s16 unk_A4;
} CL_CB9000_80171590_S_80171590_2;   /* arg0 in func_8016B590 */

typedef struct CL_CB9000_80171590_S_80171590_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} CL_CB9000_80171590_S_80171590_3;   /* (u8 *)state + ((CL_CB9000_80171590_S_80171590_0 *)state)->unk_8A.s in func_8016B590 */

/* Advances the entity along its stored path and updates movement state. */

/* Selects a movement direction and updates the actor's position and movement state.
 * move_data: the movement record (turn flags at +0x98, turn side at +0x9C); position_data: the grid cell
 * the actor stands on; actor_data: the actor. */

/* extern */

typedef struct CL_CB9000_80171F58_S_80171F58_0 {
    u8 pad_00[0x9A];
    s8 action;
    s8 action_tick;
} CL_CB9000_80171F58_S_80171F58_0;   /* state in func_8016BF58 */

typedef struct CL_CB9000_80171F58_S_80171F58_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} CL_CB9000_80171F58_S_80171F58_1;   /* render_state in func_8016BF58 */

typedef struct CL_CB9000_80171F58_S_80171F58_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} CL_CB9000_80171F58_S_80171F58_2;   /* entity in func_8016BF58 */

/* Select the overlay animation for the camera-relative facing and enter action 16. */

typedef struct CL_CB9000_80171FBC_S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} CL_CB9000_80171FBC_S_80171DA0_1;   /* held_arg2 in func_8016BFBC */

/* Checks whether the actor can transition and starts its directional effect. */

/* extern */
 /* extern */
                          /* extern */
 /* extern */

typedef struct CL_CB9000_80172180_S_80172180_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} CL_CB9000_80172180_S_80172180_0;   /* entity in func_8016C180 */

typedef struct CL_CB9000_80172180_S_80172180_1 {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[0xA];
    s8 action;
    s8 action_tick;
} CL_CB9000_80172180_S_80172180_1;   /* state in func_8016C180 */

typedef struct CL_CB9000_80172180_S_80172180_2 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} CL_CB9000_80172180_S_80172180_2;   /* render_state in func_8016C180 */

/* Finish the pending action, restore animation, and advance its entity countdown. */

/* extern */
                      /* extern */
 /* extern */
 /* extern */

typedef struct CL_CB9000_80172298_S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} CL_CB9000_80172298_S_80172628_0;   /* hold_arg0 in func_8016C298 */

/* Update entity state and flags according to the state query result. */

/* extern */
                                /* extern */
            /* extern */
                /* extern */

typedef struct S_801723DC_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_801723DC_unk_8C)(void *,void *,void *,void *);
    s32 unk_90;
} S_801723DC_0;   /* state in func_8016C3DC */

typedef struct CL_CB9000_80172458_S_80172458_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    s32 unk_A0;
    s16 unk_A4;
    s16 unk_A6;
    u16 unk_A8;
} CL_CB9000_80172458_S_80172458_0;   /* arg0 in func_8016C458 */

            /* extern */
         /* extern */
                             /* extern */
       /* extern */
              /* extern */
                      /* extern */
                      /* extern */
             /* extern */
                  /* extern */
                      /* extern */
                   /* extern */

/* Updates tile movement and height interpolation, then finalizes the action when its timer expires. */

/* extern */
                /* extern */

typedef struct S_80172944_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80172944_handler)(void *,void *,void *,void *);
} S_80172944_0;   /* state in func_8016C944 */

/* Run this action and restore the main state CL_CB9000_80172944_handler after completion. */

typedef struct CL_CB9000_801729A8_S_801729A8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} CL_CB9000_801729A8_S_801729A8_0;   /* arg0 in func_8016C9A8 */

typedef struct CL_CB9000_801729A8_S_801729A8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} CL_CB9000_801729A8_S_801729A8_3;   /* arg1 in func_8016C9A8 */

/* Advances a timed actor animation and performs its completion cleanup. */

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_1 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} CL_CB9000_80172BCC_S_func_80C953CC_1;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} CL_CB9000_80172BCC_S_func_80C953CC_2;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void *unk_2C;
} CL_CB9000_80172BCC_S_func_80C953CC_3;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_4 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void *unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x4];
    union {
        u8 u8;
        s8 s8;
    } unk_72;
    union {
        u8 u8;
        s8 s8;
    } unk_73;
} CL_CB9000_80172BCC_S_func_80C953CC_4;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_5 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} CL_CB9000_80172BCC_S_func_80C953CC_5;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_6 {
    u8 pad_00[0x24];
    s16 unk_24;
    s16 unk_26;
} CL_CB9000_80172BCC_S_func_80C953CC_6;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
} CL_CB9000_80172BCC_S_func_80C953CC_7;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_8 {
    u8 pad_00[0x6];
    s16 unk_06;
    void *unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} CL_CB9000_80172BCC_S_func_80C953CC_8;

typedef struct CL_CB9000_80172BCC_S_func_80C953CC_9 {
    u8 unk_00;
    u8 pad_01[0x9];
    u16 unk_0A;
    s32 unk_0C;
} CL_CB9000_80172BCC_S_func_80C953CC_9;

typedef struct CL_CB9000_80172BCC_Copy12 {
    u8 bytes[12];
} CL_CB9000_80172BCC_Copy12;

typedef struct CL_CB9000_80172BCC_Item {
    u8 pad[0x12];
    u8 kind;
    u8 pad2;
} CL_CB9000_80172BCC_Item;

/* Advance the actor's item action, spawn its effect, and restore its position when finished. */

typedef struct CL_CB9000_801730E0_S_801730E0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} CL_CB9000_801730E0_S_801730E0_0;   /* arg0 in func_8016D0E0 */

/* Advance the action wait states, then reset motion and switch scripts. */

/* extern */

/* Delegate this action to its resident implementation. */

/* extern */

/* Delegate this action to its resident implementation. */

/* extern */

/* Delegate this action to its resident implementation. */

/* extern */

typedef struct S_80173364_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80173364_handler)(void *,void *,void *,void *);
} S_80173364_0;   /* state in func_8016D364 */

/* Run this action and restore the main state CL_CB9000_80173364_handler when it completes. */

typedef struct CL_CB9000_8017339C_S_80173D4C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} CL_CB9000_8017339C_S_80173D4C_0;   /* arg0 in func_8016D39C */

typedef struct CL_CB9000_8017339C_S_80173D4C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
} CL_CB9000_8017339C_S_80173D4C_1;   /* arg2 in func_8016D39C */

typedef struct CL_CB9000_8017339C_S_80173D4C_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} CL_CB9000_8017339C_S_80173D4C_2;   /* arg3 in func_8016D39C */

/* Advances the actor_in action state and updates its directional animation. */

typedef struct CL_CB9000_8017372C_S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} CL_CB9000_8017372C_S_801740DC_0;   /* arg0 in func_8016D72C */

/* Updates actor state, directional animation, and the shared transition counter. */

/* extern */
                                /* extern */
                  /* extern */

typedef struct S_80173A38_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80173A38_unk_8C)(void *,void *,void *,void *);
} S_80173A38_0;   /* arg0 in func_8016DA38 */

typedef struct CL_CB9000_80173A38_S_80173A38_1 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} CL_CB9000_80173A38_S_80173A38_1;   /* arg2 in func_8016DA38 */

typedef struct CL_CB9000_80173A38_S_80173A38_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} CL_CB9000_80173A38_S_80173A38_2;   /* arg3 in func_8016DA38 */

/* Restore the main action handler after movement, or select its fallback animation. */

/* extern */
                /* extern */

typedef struct S_80173B00_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80173B00_handler)(void *,void *,void *,void *);
} S_80173B00_0;   /* state in func_8016DB00 */

/* Run this action and restore the main state CL_CB9000_80173B00_handler after completion. */

/* extern */

typedef struct S_80173B64_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80173B64_handler)(void *,void *,void *,void *);
} S_80173B64_0;   /* state in func_8016DB64 */

/* Run this action and restore the main state CL_CB9000_80173B64_handler when it completes. */

/* extern */

typedef struct S_80173B9C_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80173B9C_handler)(void *,void *,void *,void *);
} S_80173B9C_0;   /* state in func_8016DB9C */

/* Run this action and restore the main state CL_CB9000_80173B9C_handler when it completes. */

/* extern */

typedef struct S_80173BD4_0 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80173BD4_handler)(void *,void *,void *,void *);
} S_80173BD4_0;   /* state in func_8016DBD4 */

/* Run this action and restore the main state CL_CB9000_80173BD4_handler when it completes. */

/* Fade the primitive color and flag the effect when its countdown expires. */

typedef struct {
    u32 word[3];
} __attribute__((packed)) CL_CB9000_80173CFC_Copy12;

typedef struct CL_CB9000_80173CFC_S_80173CFC_0 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x21];
    s16 unk_24;
} CL_CB9000_80173CFC_S_80173CFC_0;   /* part in func_8016DCFC */

typedef struct CL_CB9000_80173CFC_S_80173CFC_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} CL_CB9000_80173CFC_S_80173CFC_1;   /* data in func_8016DCFC */

/* Creates an effect at an offset from the source position with randomized rotation. */

typedef struct CL_CB9000_80173E40_S_80173E40_0 {
    u8 pad_00[0x24];
    union { u8 * p; u32 * p2; } unk_24;   /* accessed as both */
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} CL_CB9000_80173E40_S_80173E40_0;   /* scratch in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} CL_CB9000_80173E40_S_80173E40_1;   /* arg1 in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_2 {
    u8 pad_00[0xF];
    u8 unk_0F;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} CL_CB9000_80173E40_S_80173E40_2;   /* arg2 in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
    u8 pad_B4[0x81C];
    u8 * unk_8D0;
} CL_CB9000_80173E40_S_80173E40_3;   /* *(u8 **)D_80083160 in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_4 {
    u32 unk_00;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u32 unk_14;
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
} CL_CB9000_80173E40_S_80173E40_4;   /* packet in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} CL_CB9000_80173E40_S_80173E40_5;   /* state in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_6 {
    u8 pad_00[0x4];
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u8 pad_14[0x30];
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
    u16 unk_4E;
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
} CL_CB9000_80173E40_S_80173E40_6;   /* arg0 in func_8016DE40 */

typedef struct CL_CB9000_80173E40_S_80173E40_7 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} CL_CB9000_80173E40_S_80173E40_7;   /* *(u8 **)global in func_8016DE40 */

typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} CL_CB9000_80173E40_MATRIX;

/* Projects a quad and adds it to the ordering table when visible. */

typedef struct CL_CB9000_80174320_S_80174320_0_pre {
    void * unk_00;
    u8 pad_04[0x4];
} CL_CB9000_80174320_S_80174320_0_pre;   /* the 0x8 bytes before var_s0 in func_8016E320, addressed as var_s0[-1] */

typedef struct CL_CB9000_80174320_S_80174320_1 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
} CL_CB9000_80174320_S_80174320_1;   /* temp_a2 in func_8016E320 */

/* extern */

/* Render every point in the linked effect chain. */

#define F8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FU16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/* Update an effect's color phases, burst, movement, and remaining lifetime. */

typedef struct CL_CB9000_80174724_S_80C96F24_0 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} CL_CB9000_80174724_S_80C96F24_0;   /* arg0 in func_8016E724 */

typedef struct CL_CB9000_80174724_S_80C96F24_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x21];
    s16 unk_24;
    s16 unk_26;
    u8 pad_28[0x2];
    s16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x16];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} CL_CB9000_80174724_S_80C96F24_1;   /* work in func_8016E724 */

typedef struct CL_CB9000_80174724_S_80C96F24_2 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} CL_CB9000_80174724_S_80C96F24_2;   /* arg0_reload in func_8016E724 */

typedef struct CL_CB9000_80174724_S_80C96F24_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} CL_CB9000_80174724_S_80C96F24_3;   /* obj in func_8016E724 */

typedef struct CL_CB9000_80174724_S_80C96F24_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} CL_CB9000_80174724_S_80C96F24_4;   /* state in func_8016E724 */

typedef struct CL_CB9000_80174724_S_80C96F24_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} CL_CB9000_80174724_S_80C96F24_6;   /* arg1_reload in func_8016E724 */

typedef struct CL_CB9000_80174724_S_80C96F24_7 {
    u8 pad_00[0xA4];
    u16 unk_A4;
} CL_CB9000_80174724_S_80C96F24_7;   /* arg0_counter in func_8016E724 */

typedef struct {
    u8 bytes[12];
} CL_CB9000_80174724_Copy12;

extern void *memcpy(void *, const void *, u32);

/* Create three bands of eight effect segments around the supplied position. */

/* extern */

typedef struct CL_CB9000_80174B3C_S_80174B3C_0 {
    u8 pad_00[0x6D];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} CL_CB9000_80174B3C_S_80174B3C_0;   /* entity in func_8016EB3C */

typedef struct S_80174B3C_1 {
    u8 pad_00[0x8C];
    void (*CL_CB9000_80174B3C_handler)();
    u8 pad_90[0xA];
    s8 action;
    s8 action_tick;
} S_80174B3C_1;   /* state in func_8016EB3C */

typedef struct CL_CB9000_80174B3C_S_80174B3C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} CL_CB9000_80174B3C_S_80174B3C_2;   /* &D_80083460 in func_8016EB3C */

/* Enter action 23, then release the state CL_CB9000_80174B3C_handler when the entity action completes. */

/* Processes input, then blends three state channels toward 0x80 and marks completion. */

typedef struct CL_CB9000_80174D14_S_80C97514_12 {
    u8 pad_00[0x8];
    void * unk_08;
} CL_CB9000_80174D14_S_80C97514_12;   /* temp_v0_2 in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_15 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} CL_CB9000_80174D14_S_80C97514_15;   /* ((Rec_D_80082E80 *)arg3)->unk_60.as_pv in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_0_pre {
    u16 unk_00;
} CL_CB9000_80174D14_S_80C97514_0_pre;   /* the 0x2 bytes before arg0 in func_8016ED14, addressed as arg0[-1] */

typedef struct CL_CB9000_80174D14_S_80C97514_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s16 unk_A4;
    u8 pad_A6[0x6];
    void * unk_AC;
} CL_CB9000_80174D14_S_80C97514_0;   /* arg0 in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_2 {
    u8 unk_00;
} CL_CB9000_80174D14_S_80C97514_2;   /* &D_8016F3A9 in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} CL_CB9000_80174D14_S_80C97514_4;   /* temp_a1 in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_5 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
} CL_CB9000_80174D14_S_80C97514_5;   /* temp_v0_2 in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_7 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} CL_CB9000_80174D14_S_80C97514_7;   /* temp_s0 in func_8016ED14 */

typedef struct CL_CB9000_80174D14_S_80C97514_9_pre {
    void * unk_00;
    u8 pad_04[0x10];
} CL_CB9000_80174D14_S_80C97514_9_pre;   /* the 0x14 bytes before temp_v1_3 in func_8016ED14, addressed as temp_v1_3[-1] */

typedef struct CL_CB9000_80174D14_S_80C97514_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} CL_CB9000_80174D14_S_80C97514_9;   /* temp_v1_3 in func_8016ED14 */

/* cfail-repair: tf7-phase1-cache-v3 */
     /* extern */
s32 Control_CD(); /* extern */
 /* extern */
 /* extern */
                           /* extern */
           /* extern */
              /* extern */
                /* extern */
                          /* extern */
                      /* extern */
             /* extern */
                 /* extern */
                /* extern */
                     /* extern */
     /* extern */
 /* extern */
      /* extern */

/* Advances the actor transition through turning, color blending, effects, and model replacement. */

typedef void (*CL_CB9000_8017523C_ActionCallback)(void *,void *,void *,void *);
typedef struct {
 u8 pad[0x8C];
 CL_CB9000_8017523C_ActionCallback handler;
} CL_CB9000_8017523C_CallbackState;

/* Resume the action dispatcher after the resident action completes. */

typedef void (*CL_CB9000_80175274_ActionCallback)(void *,void *,void *,void *);
typedef struct {
 u8 pad[0x8C];
 CL_CB9000_80175274_ActionCallback handler;
} CL_CB9000_80175274_CallbackState;

/* Resume the action dispatcher after the resident action completes. */
extern s32 resource_completion_callback_address[];
extern s16 actor_turn_angle_offsets[];
extern s32 cd_cue_base;
extern u16 reference_tile_position_alias;
extern DungeonGlobalStatus D_80083460;
extern u16 dungeon_status_flags_alias;
extern void *actor_effect_color_targets[];
extern s8 staged_spawn_count;
extern s16 actor_action_reset_value;
extern u8 dungeon_resource_buffer[];
extern u8 D_8016F2AC[];
extern u8 D_8016F2B4[];
extern u8 D_8016F2BC[8];
extern u8 D_8016F2C4[8];
extern u8 D_8016F2CC[];
extern u8 D_8016F2D4[];
extern u8 D_8016F2DC[];
extern M2C_UNK D_8016F2E4;
extern u8 D_8016F2EC[8];
extern u8 D_8016F2F4[8];
extern u8 cb9000_frame_set_1[];
extern u8 cb9000_status_frames[];
extern s32 D_8016F30C;
extern s16 D_8016F314;
extern u8 D_8016F318[];
extern u8 D_8016F324[12];
extern u8 D_8016F330[12];
extern CL_CB9000_80170C24_Callback D_8016F33C[];
extern CL_CB9000_80172BCC_Copy12 D_8016F39C;
extern u8 D_8016F3A8;
extern u8 D_8016F3A9;
extern s32 D_8016F3AC;
extern int abs(int);
extern void select_record_entry_and_value();
extern void sound_set_cd_cue_parameters();
extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void run_cd_image_commands();
extern void func_80041588();
extern void initialize_timed_motion_step(s32, s32);
extern s32 get_entity_effect_value(void *, s32);
extern s32 func_80042900(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void func_80042B68(void *, s32);
extern int read_stream_cue_start_offset();
extern void register_node(CL_CB9000_8017087C_Object *, void *);
extern void func_8004491C(CL_CB9000_8017087C_Object *, void *);
extern void unlink_node(void *node);
extern void func_80044A50(void *node);
extern void select_indirect_table_entry();
extern void select_sprite_entry(void *, s16, s16);
extern void func_80047784(void *, s16, s16);
extern void advance_sprite_animation_and_textures();
extern s32 lookup_masked_byte_table();
extern s32 rsin(s32);
extern s32 rcos(s32);
extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void RotMatrix(void *, void *);
extern u16 GetTPage(s32, s32, s32, s32);
extern void SetPolyG4(void *);
extern void SetDrawMode(void *, s32, s32, u16, s32);
extern s32 rand(void);
extern void unlink_entity_node();
extern s32 check_entity_relation(void *,void *);
extern s32 cycle_map_cell_flags();
extern s32 update_map_cell_flags_with_item_limit();
extern s16 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 check_movement_clearance_and_height(s16,void *,void *,s32);
extern void resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void prepare_directional_attack(void *, void *, s16, s32, s32);
extern s32 find_active_rect_containing_point(s32, s32);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s32 test_neighbor_position_relation(s32,s32,s32,s32);
extern s16 get_actor_height_difference(void *,void *);
extern void apply_monster_koyaw_data();
extern void *find_adjacent_actor(void *, u8, u8);
extern s32 probe_directional_neighbor();
extern void *scan_actor_along_heading(void *, s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16,s16,s16,s16,u16 *);
extern void select_actor_route_target(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern void decrement_monster_entry_count();
extern void update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 can_entity_gain_level(void *);
extern void set_record_integer_tile_center(void *, s32, s32);
extern s32 try_claim_dungeon_action_slot(void *);
extern s32 has_pending_dungeon_activity(void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 check_entity_interaction_compatibility();
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern s32 advance_status_timers(void *);
extern s32 advance_staged_entity_load();
extern void play_sound_if_enabled(s32);
extern s32 generate_random_value();
extern s32 create_actor_spell_effect(void *, void *, s32, void *);
extern void on_actor_status_updated(void *);
extern void func_800A9A04(void *);
extern void update_actor_status_and_mp(void *);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s16);
extern s32 refresh_actor_facing_and_lifecycle();
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, s32, void *, u8 *);
extern s32 advance_actor_pending_action(void *, s32, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, s32, void *, u8 *);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern s32 process_selected_actor_record(void *, s32, void *, void *);
extern void begin_actor_spell_action(void *, s32, void *, u8 *, s32);
extern s32 update_actor_movement_to_tile(void *,void *,void *,void *);
extern s32 update_linked_actor_motion(void *,void *,void *,void *);
extern s32 resolve_actor_floor_trap_once(void *,void *,void *,void *);
extern s32 update_actor_hop_and_shrink(void *,void *,struct SpriteFrameState *,void *);

extern s32 update_actor_hop_and_grow(void *,void *,void *,void *);
extern s32 update_thrown_actor_travel(void *,void *,struct SpriteFrameState *,void *);
extern s32 interpolate_actor_to_terrain_tile(void *,void *,void *,void *);
extern s32 update_spinning_actor_fall(void *,void *,void *,void *);
extern s32 propagate_actor_action_flag(void *,void *,void *,void *);
extern s32 update_actor_transform_from_parent(void *,void *,void *,void *);
extern s32 update_actor_fade_in(void *,void *,void *);
extern s32 update_actor_defeat_removal(void *,void *,void *,void *);
extern void apply_clamped_actor_value_delta(void *);
extern void spend_actor_mp(void *, s32);

extern s32 create_status_linked_render_effect();
extern s32 relink_entity_and_clear_high_flag();
/* Retail banks use the signed-halfword height-query return view; this
 * is the existing certified fa7000 contract, not a per-function flag. */
extern s16 sample_terrain_surface_height(s32,s32,s16);
extern s32 select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s32 slot_value);
extern void apply_camera_offset_and_select_target(void *, void *, s32, s32);
extern s32 rand(void);

void initialize_gray_sprite_copy(CL_CB9000_8017087C_Object *object, s32 field60_value, CL_CB9000_8017087C_CopyFields *source_coords);
void func_8016A920(void *effect, void *unused, void *visual);
void *func_8016AA5C(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
void func_8016AC24(void *entity, CL_CB9000_80170C24_S_80170C24_2 *motion, void *monster);
void func_8016B02C(CL_CB9000_8017102C_S_8017102C_0 *state, void *motion, CL_CB9000_8017102C_S_8017102C_2 *sprite, CL_CB9000_8017102C_S_8017102C_1 *actor);
void func_8016B590(void *motion, s32 update_param, void *entity, void *state);
void func_8016B810(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);
void func_8016BF58(CL_CB9000_80171F58_S_80171F58_0 *state, void *unused_position, CL_CB9000_80171F58_S_80171F58_1 *render_state, CL_CB9000_80171F58_S_80171F58_2 *entity);
s32 func_8016BFBC(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, ActorRecord *actor);
void func_8016C180(CL_CB9000_80172180_S_80172180_1 *state, s32 position, CL_CB9000_80172180_S_80172180_2 *render_state, void *entity);
s32 func_8016C298(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_8016C3DC(void *state_arg,void *position,void *render_state,void *entity);
void func_8016C458(void *action, struct ObjectPosition *motion, struct SpriteFrameState *map_entry, ActorRecord *actor);
void func_8016C944(S_80172944_0 *state,void *position,void *render_state,void *entity);

void func_8016CBCC(CL_CB9000_80172BCC_S_func_80C953CC_1 *work, CL_CB9000_80172BCC_S_func_80C953CC_2 *position, CL_CB9000_80172BCC_S_func_80C953CC_3 *entity,
    CL_CB9000_80172BCC_S_func_80C953CC_4 *actor);
void update_hop_to_tile_and_complete(CL_CB9000_801730E0_S_801730E0_0 *state, struct ObjectPosition *motion, struct SpriteFrameState *action, EntityRec *entity);
void func_8016D304(void *state,void *position,void *render_state,void *entity);
void func_8016D324(void *state,void *position,void *render_state,void *entity);
void func_8016D344(void *state,void *position,void *render_state,void *entity);
void func_8016D364(S_80173364_0 *state,void *position,void *render_state,void *entity);
void func_8016D39C(void *action, void *context, void *sprite_in, void *actor_in);
void func_8016D72C(void *actor_in, s32 actor_index, void *target, void *entity_in);
void func_8016DA38(S_80173A38_0 *state, void *position, CL_CB9000_80173A38_S_80173A38_1 *sprite, CL_CB9000_80173A38_S_80173A38_2 *actor);
void func_8016DB00(S_80173B00_0 *state,void *position,void *render_state,void *entity);
void func_8016DB64(S_80173B64_0 *state,void *position,void *render_state,void *entity);
void func_8016DB9C(S_80173B9C_0 *state,void *position,void *render_state,void *entity);
void func_8016DBD4(S_80173BD4_0 *state,void *position,void *render_state,void *entity);
void func_8016DC0C(void *effect, s32 unused, void *primitive);
void func_8016DCFC(void *unused_context, Rec_func_80173CFC_arg1 *source_pos, s32 unused_value, s16 scale);
void func_8016DE40(void *quad, void *position, void *render_info, s16 depth_bias);
s32 func_8016E320(void *point, void *position, void *color);
void func_8016E374(u8 *effect, s32 *position, s32 effect_param);
void func_8016E724(CL_CB9000_80174724_S_80C96F24_0 *owner, void *origin, void *entity);
void func_8016EB3C(S_80174B3C_1 *state, void *unused_position, void *unused_render_state, CL_CB9000_80174B3C_S_80174B3C_0 *entity);
void func_8016EBE8(u8 *task, void *context, u8 *input);
void func_8016ED14(void *state, EntityRec *position, struct SpriteFrameState *entity, void *actor);
void func_8016F23C(CL_CB9000_8017523C_CallbackState *state,void *position,void *sprite,void *entity);
void func_8016F274(CL_CB9000_80175274_CallbackState *state,void *position,void *sprite,void *entity);
#endif
