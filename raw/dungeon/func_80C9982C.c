#ifndef MODULE_DUNGEON_OVL_CB9000_H
#define MODULE_DUNGEON_OVL_CB9000_H
#include "common.h"
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

typedef struct CL_CB9000_80170A5C_S_80170A5C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} CL_CB9000_80170A5C_S_80170A5C_0;   /* object in func_8016AA5C */

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

typedef struct CL_CB9000_80170A5C_S_80170A5C_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} CL_CB9000_80170A5C_S_80170A5C_3;   /* part1 in func_8016AA5C */

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
    M2C_UNK * unk_2C;
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
    M2C_UNK * unk_2C;
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
    M2C_UNK * unk_2C;
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

typedef struct CL_CB9000_80173CFC_S_80173CFC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} CL_CB9000_80173CFC_S_80173CFC_2;   /* pos in func_8016DCFC */


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

typedef struct CL_CB9000_80174724_S_80C96F24_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} CL_CB9000_80174724_S_80C96F24_5;   /* position in func_8016E724 */

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


typedef struct CL_CB9000_80174D14_S_80C97514_14 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} CL_CB9000_80174D14_S_80C97514_14;   /* ((CL_CB9000_80174D14_S_80C97514_12 *)temp_v0_2)->unk_08 in func_8016ED14 */

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
extern s32 D_8003E140[];
extern s16 D_8006CD00[];
extern s32 D_8006CD58;
extern u16 D_80082EA4;
extern M2C_UNK D_80083460;
extern u16 D_80083462;
extern void *D_800DCEEC[];
extern s8 D_800DCF5C;
extern s16 D_800DCF5E;
extern u8 D_8014A000[];
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
extern u8 D_8016F2FC[];
extern u8 D_8016F304[];
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
extern void func_8003DB94();
extern s32 func_8003F270(void);
extern void func_8003F540();
extern void *func_8003FD64(s32, void *);
extern void func_80041588();
extern void func_800419EC(s32, s32);
extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern int func_800445E0();
extern void func_8004491C(CL_CB9000_8017087C_Object *, void *);
extern void func_80044A50(void *node);
extern void func_80047738();
extern M2C_UNK func_80047784(void *, u8, M2C_UNK);
extern void func_800478B8();
extern s32 func_800498A0();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern s32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u16 func_80066460(s32, s32, s32, s32);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, u16, s32);
extern s32 func_80069EF8(void);
extern void func_8009A028();
extern s32 func_8009A180(void *,void *);
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 func_8009A66C(s16,void *,void *,s32);
extern void func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance);
extern void func_8009C93C(void *, void *, s16, M2C_UNK, s32);
extern s32 func_8009FB34(s32, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_8009FD7C(s32,s32,s32,s32);
extern s16 func_800A0134(void *,void *);
extern void func_800A020C();
extern void *func_800A02AC(void *, u8, u8);
extern s32 func_800A04F0();
extern void *func_800A05A4(void *, s32, s32, s32, s32);
extern s32 func_800A0818(s16,s16,s16,s16,u16 *);
extern void func_800A0E6C(u8 *actor_held, s32 kind, u8 *work_p, u16 *out);
extern void func_800A18E8();
extern void func_800A19E4(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 func_800A1C58(void *);
extern void func_800A2B04(void *, s32, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2BDC(void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A2CB8();
extern void func_800A48F0(void *, s32, s32);
extern M2C_UNK func_800A4ACC(M2C_UNK);
extern s32 func_800A504C();
extern void func_800A56E0(s32);
extern s32 func_800A6D30();
extern s32 func_800A94A0(void *, void *, s32, void *);
extern void func_800A9A04(void *);
extern M2C_UNK func_800A9A0C(void *);
extern void func_800A9C18(void *, void *, void *, s16);
extern s32 func_800A9E70();
extern M2C_UNK func_800AA258(void *, M2C_UNK, void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK *);
extern M2C_UNK func_800AA79C(void *, M2C_UNK, void *, void *);
extern M2C_UNK func_800AA888(void *, M2C_UNK, void *, void *);
extern s32 func_800AA924(void *, M2C_UNK, void *, M2C_UNK *);
extern void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants);
extern s32 func_800AAB10(void *, M2C_UNK, void *, void *);
extern M2C_UNK func_800AAF00(void *, M2C_UNK, void *, M2C_UNK *, void (*)(void *, M2C_UNK, void *, void *));
extern s32 func_800AB1C0(void *,void *,void *,void *);
extern s32 func_800AB378(void *,void *,void *,void *);
extern s32 func_800AB464(void *,void *,void *,void *);
extern s32 func_800AB538(void *,void *,void *,void *);
extern s32 func_800AB778(void *,void *,void *,void *);
extern s32 func_800ABDBC(void *,void *,void *,void *);
extern s32 func_800AC010(void *,void *,void *,void *);
extern s32 func_800AC480(void *,void *,void *,void *);
extern s32 func_800AC5C8(void *,void *,void *,void *);
extern s32 func_800AC7EC(void *,void *,void *,void *);
extern s32 func_800AC82C(void *,void *,void *,void *);
extern s32 func_800ACE34(void *,void *,void *);
extern s32 func_800AD058(void *,void *,void *,void *);
extern void func_800AD4D0(void *);
extern M2C_UNK func_800AD594(M2C_UNK, M2C_UNK);
extern s32 func_800AD9B4(void *,void *);
extern s32 func_800ADC4C();
extern s32 func_800ADDA0();
extern void func_800B66C8(void *);
/* Retail banks use the signed-halfword height-query return view; this
 * is the existing certified fa7000 contract, not a per-function flag. */
extern s16 func_800BCB04(s32,s32,s16);
extern s32 func_800C77D0();
extern void func_800C7930(void *, M2C_UNK, M2C_UNK, M2C_UNK);
extern s32 rand(void);

void func_8016A87C(CL_CB9000_8017087C_Object *object, s32 field60_value, CL_CB9000_8017087C_CopyFields *source_coords);
void func_8016A920(void *effect, void *unused, void *visual);
void *func_8016AA5C(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);
void func_8016AC24(void *entity, CL_CB9000_80170C24_S_80170C24_2 *motion, void *monster);
void func_8016B02C(CL_CB9000_8017102C_S_8017102C_0 *state, void *motion, CL_CB9000_8017102C_S_8017102C_2 *sprite, CL_CB9000_8017102C_S_8017102C_1 *actor);
void func_8016B590(void *motion, s32 update_param, void *entity, void *state);
void func_8016B810(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, EntityRec *actor_data);
void func_8016BF58(CL_CB9000_80171F58_S_80171F58_0 *state, void *unused_position, CL_CB9000_80171F58_S_80171F58_1 *render_state, CL_CB9000_80171F58_S_80171F58_2 *entity);
s32 func_8016BFBC(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, EntityRec *actor);
void func_8016C180(CL_CB9000_80172180_S_80172180_1 *state, M2C_UNK position, CL_CB9000_80172180_S_80172180_2 *render_state, void *entity);
s32 func_8016C298(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void func_8016C3DC(void *state_arg,void *position,void *render_state,void *entity);
void func_8016C458(void *action, EntityRec *motion, void *map_entry, EntityRec *actor);
void func_8016C944(S_80172944_0 *state,void *position,void *render_state,void *entity);
void func_8016C9A8(void *action, void *motion, void *sprite, void *actor);
void func_8016CBCC(CL_CB9000_80172BCC_S_func_80C953CC_1 *work, CL_CB9000_80172BCC_S_func_80C953CC_2 *position, CL_CB9000_80172BCC_S_func_80C953CC_3 *entity,
    CL_CB9000_80172BCC_S_func_80C953CC_4 *actor);
void func_8016D0E0(CL_CB9000_801730E0_S_801730E0_0 *state, EntityRec *motion, Rec_D_80082E80 *action, EntityRec *entity);
void func_8016D304(void *state,void *position,void *render_state,void *entity);
void func_8016D324(void *state,void *position,void *render_state,void *entity);
void func_8016D344(void *state,void *position,void *render_state,void *entity);
void func_8016D364(S_80173364_0 *state,void *position,void *render_state,void *entity);
void func_8016D39C(void *action, void *context, void *sprite_in, void *actor_in);
void func_8016D72C(void *actor_in, s32 actor_index, void *target, void *entity_in);
void func_8016DA38(S_80173A38_0 *arg0, void *arg1, CL_CB9000_80173A38_S_80173A38_1 *arg2, CL_CB9000_80173A38_S_80173A38_2 *arg3);
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
void func_8016ED14(void *state, EntityRec *position, Rec_D_80082E80 *entity, void *actor);
void func_8016F23C(CL_CB9000_8017523C_CallbackState *state,void *position,void *sprite,void *entity);
void func_8016F274(CL_CB9000_80175274_CallbackState *state,void *position,void *sprite,void *entity);
#endif



void func_8016B02C(CL_CB9000_8017102C_S_8017102C_0 *state, void *motion, CL_CB9000_8017102C_S_8017102C_2 *sprite, CL_CB9000_8017102C_S_8017102C_1 *actor) {
 u16 terrain_flags;
 u8 *frames;
 s32 room;
 s32 actor_flags;
 u16 flags;
 if(dungeonStatus.flags & 0x1000) {
  state->unk_9A=14;
  func_8016B590(state,motion,sprite,actor);
  return;
 }
 if(actor->unk_25==0) {
  func_800AA79C(state,motion,sprite,actor);
  if(sprite->unk_2C==D_8016F2FC) return;
  sprite->unk_2C=D_8016F2F4;
  func_80047784(sprite,D_8016F2F4[((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
  return;
 }
 {
  if(actor->unk_1C & 0x200) {
   if(sprite->unk_2C==D_8016F2FC) {
    state->unk_9A=13;
    state->unk_9B=1;
    state->unk_8C=0;
    actor->unk_1C &= 0xFFFBFFFF;
    return;
   }
   if(func_800AA924(state,motion,sprite,D_8016F2F4)!=0) return;
  }
  if(!(dungeonStatus.flags & 0x2000)) {
   if(actor->unk_1C & 0x100) {
    func_800AA258(state,motion,sprite,actor);
    return;
   }
   if(state->unk_9A!=14) {
    if(sprite->unk_2C!=D_8016F2B4) {
     sprite->unk_2C=D_8016F2B4;
     func_80047784(sprite,D_8016F2B4[((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
    }
    state->unk_9A=14;
   }
   state->unk_98 &= 0xFFF3;
   if(actor->unk_64!=0 && func_800AA6B4(state,motion,sprite,D_8016F2BC)!=0) return;
   if(actor->unk_1C & 0x80000) {
    func_800AA888(state,motion,sprite,actor);
    func_8016DA38(state,motion,sprite,actor);
    return;
   }
   if((func_800A1C58(actor)<<16)!=0 && (func_800AAB10(state,motion,sprite,actor)<<16)!=0)
    func_8016EB3C(state,motion,sprite,actor);
  }
  room=func_8009FB34(sprite->tile.bytes.x,sprite->tile.bytes.y);
  sprite->unk_26=room;
  if(actor->unk_6D>0) {
   if(actor->unk_1C & 0x20) {
    func_800A9A0C(actor);
    return;
   }
   if(sprite->tile.packed==D_80082EA4) {
    func_8016B810(state,motion,sprite,actor);
    return;
   }
   if(!(actor->unk_46 & 0x8000)) {
    if((!(dungeonStatus.flags & 0x2000) || (func_8009A180(actor,((CL_CB9000_8017102C_S_8017102C_3 *)D_800814A8)->unk_58+0x20)<<16)==0)
       && (func_8016C298(state,motion,sprite,0)<<16)!=0) {
     flags=actor->unk_46 | 0x4000;
     actor->unk_46=flags;
     if(!(flags & 0x8000)) {
      func_8016B810(state,motion,sprite,actor);
      return;
     }
    } else return;
   }
   switch(actor->unk_46 & 0x3FFF) {
   case 8: case 9:
    if((func_8016BFBC(state,motion,sprite,actor)<<16)==0)
     func_8016C180(state,motion,sprite,actor);
    return;
   case 5: case 6: case 7:
    actor->unk_2A=func_800A0818(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
    if(((CL_CB9000_8017102C_S_8017102C_3 *)D_800814A8)->unk_9A==17) {
     func_800AAF00(state,motion,sprite,D_8016F2EC,func_8016B02C);
     return;
    }
    /* A failed pursuit falls through to the same completion path as action 12. */
   case 12:
    func_800A9A0C(actor);
    return;
   case 1: case 2: case 3:
    func_800AAF00(state,motion,sprite,D_8016F2EC,func_8016B02C);
    return;
   default:
    func_8016B810(state,motion,sprite,actor);
    return;
   }
  }
  actor_flags=actor->unk_1C;
  if(!(actor_flags & 0x2000) && ((s8)room<0 || !(((CL_CB9000_8017102C_S_8017102C_5 *)((u8 *)D_800E2970+(s8)room*20))->unk_0C & 2)) && !(actor_flags & 0x430)) {
   if((func_8009FD7C(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY)<<16)!=0)
    actor->unk_2A=func_800A0818(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
  }
  if((dungeonStatus.flags & 0x2000) || (sprite->unk_14 & 0x40)) return;
  frames=D_8016F2B4;
  if(sprite->unk_2C==frames) return;
 }
 sprite->unk_2C=frames;
 func_80047784(sprite,*((((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7)+frames),0);
}
