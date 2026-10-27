#include "engine/node/allocation.h"
#ifndef DUNGEON_EFFECT_EXPIRING_SPRITE_EFFECT_G00370_H
#define DUNGEON_EFFECT_EXPIRING_SPRITE_EFFECT_G00370_H
/* Expiring sprite effect shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800D1374. */

#include "common.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

/* M2C_UNK comes from m2c_compat.h. */

typedef struct S_800D6AD4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800D6AD4_0;

typedef struct S_800D6AD4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800D6AD4_1;

typedef struct S_800D6AD4_2 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800D6AD4_2;

typedef struct S_800D6AD4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800D6AD4_3;

typedef struct S_800D6AD4_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_800D6AD4_4;

typedef struct S_800D6AD4_5 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_800D6AD4_5;

typedef struct S_800D6C18_0_pre {
    u16 unk_00;
} S_800D6C18_0_pre;

/* the 0x2 bytes before arg0 in update_expiring_sprite_effect, addressed as arg0[-1] */
typedef struct S_800D6C18_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u8 pad_18[0x3C];
    s16 unk_54;
    s16 unk_56;
} S_800D6C18_0;

/* arg0 in update_expiring_sprite_effect */
typedef struct S_800D6C18_1 {
    u8 pad_00[0x14];
    u32 unk_14;
} S_800D6C18_1;

typedef struct S_800D6C18_2 {
    u8 pad_00[0x14];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800D6C18_2;

/* arg1 in update_expiring_sprite_effect */
typedef struct S_800D6C18_3 {
    u8 pad_00[0x44];
    s16 unk_44;
    u8 pad_46[0x6];
    s16 unk_4C;
} S_800D6C18_3;

/* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in create_offset_sprite_effect */
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern M2C_UNK D_800D6804[3];
extern M2C_UNK D_800D68F4[3];

/* Functions defined in this translation unit. */
void create_offset_sprite_effect(ObjectNodeHeader *parent, s32 state_value, s16 x_offset, s16 y_offset, s32 z_offset, s32 motion_scale);
void update_expiring_sprite_effect(void *effect, S_800D6C18_2 *size_state);

#endif
