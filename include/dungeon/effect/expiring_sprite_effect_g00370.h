#include "engine/node/allocation.h"
#ifndef DUNGEON_EFFECT_EXPIRING_SPRITE_EFFECT_G00370_H
#define DUNGEON_EFFECT_EXPIRING_SPRITE_EFFECT_G00370_H
/* Expiring sprite effect shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D1374. */

#include "common.h"
#include "dungeon/effect/radial_effect_segment.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "engine/node.h"

/* M2C_UNK comes from m2c_compat.h. */

typedef struct S_800D6AD4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800D6AD4_0;

typedef struct S_800D6AD4_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_800D6AD4_5;

typedef struct S_800D6C18_1 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_800D6C18_1;

typedef struct S_800D6C18_2 {
    u8 pad_00[0x14];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800D6C18_2;

/* arg1 in update_expiring_sprite_effect */
/* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in create_offset_sprite_effect */



/* Functions defined in this translation unit. */
void create_offset_sprite_effect(ObjectNodeHeader *parent, s32 state_value, s16 x_offset, s16 y_offset, s32 z_offset, s32 motion_scale);
void update_expiring_sprite_effect(RadialEffectSegmentBody *effect, S_800D6C18_2 *size_state);

#endif
