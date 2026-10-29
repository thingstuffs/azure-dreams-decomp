#ifndef DUNGEON_EFFECT_RADIAL_BURST_G00343_H
#define DUNGEON_EFFECT_RADIAL_BURST_G00343_H
/* Radial burst shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B10B4. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct DungeonEffect {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 field_A;
    s32 field_C;
    s32 field_10;
    u8 pad14[2];
    s16 field_16;
    u16 flags;
} DungeonEffect;

typedef struct S_800B6814_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B6814_0;

/* node in spawn_randomized_radial_burst */

/* part in spawn_randomized_radial_burst */
/* arg0 in spawn_randomized_radial_burst */
typedef struct S_800B6814_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800B6814_3;

extern s32 rsin(s32);
extern s32 rcos(s32);
extern s32 rand(void);
extern void get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
/* param_width floor: keep this local s16 declaration; the owner prototype changes this call's argument setup. */
extern void spawn_opposite_offset_effect(DungeonEffect *, s16);
/* sub in spawn_randomized_radial_burst */
extern void register_node(void *, void *);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 radial_burst_callback;
extern s32 directional_sprite_entries;

/* Functions defined in this translation unit. */
void spawn_randomized_radial_burst(MovingPosition *origin);

#endif
