#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#ifndef MODULE_DUNGEON_OVL_D5B0B8_H
#define MODULE_DUNGEON_OVL_D5B0B8_H

#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "engine/node/allocation.h"

typedef struct S_80D3B0B8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    ObjectNodeHeader * unk_AC;
} S_80D3B0B8_0;   /* temp_s3 in func_801708B8 */

   /* saved_arg1 in func_801708B8 */

typedef struct Copy16 {
    s32 word[4];
} Copy16;

typedef struct { Copy16 block[3]; } Copy48;

extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern void create_tracked_effect(void *, s32, void *, void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

extern u8 D_800D5594[];
extern s8 view_direction_depth_biases[];
extern u8 D_800E23F0[];

/* Creates an owner-linked object with copied position and direction-adjusted sprite data. */
#endif
