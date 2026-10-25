#ifndef TOWN_MENU_PAIRED_OFFSET_EFFECTS_G00579_H
#define TOWN_MENU_PAIRED_OFFSET_EFFECTS_G00579_H
/* inferred-strong G00579: paired_offset_effects_g00579; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A97E8. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_payload.h"
#include "shared/vector.h"

typedef struct S_800A6F48_14 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_14;

typedef struct S_800A6F48_15 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800A6F48_15;

typedef struct S_800A6F48_0 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_800A6F48_0;

/* arg1 in create_paired_offset_effects */
typedef struct S_800A6F48_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_1;

/* &D_800D0DD8 in create_paired_offset_effects */
/* arg2 in create_paired_offset_effects */
typedef struct S_800A6F48_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_3;

typedef struct S_800A6F48_4 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_4;

typedef struct S_800A6F48_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_5;

typedef struct S_800A6F48_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800A6F48_6;

typedef struct S_800A6F48_7 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_800A6F48_7;

typedef struct S_800A6F48_8 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0xA4];
    s16 unk_B0;
} S_800A6F48_8;

typedef struct S_800A6F48_9 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800A6F48_9;

typedef struct S_800A6F48_10 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800A6F48_10;

/* arg0 in create_paired_offset_effects */
typedef struct S_800A6F48_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800A6F48_11;

#include "town/menu/object/create_positioned_sprite_object_g01142.h"
/* extern */
void spawn_person_radial_effects(void *source);
/* extern */
extern void D_800A70EC();
extern M2C_UNK D_800D0DD8;

/* Functions defined in this translation unit. */
void accumulate_effect_step(void *updateState, s32 unused1, s32 unused2, void *accumulatorState);
void create_paired_offset_effects(S_800A6F48_10 *owner, S_800A6F48_0 *spawn_state, IntVector3 *origin, S_800A6F48_11 *color);

#endif
