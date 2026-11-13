#ifndef DUNGEON_EFFECT_RADIAL_BURST_G00343_H
#define DUNGEON_EFFECT_RADIAL_BURST_G00343_H
/* Radial burst shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B10B4. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"

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

/* param_width floor: keep this local s16 declaration; the owner prototype changes this call's argument setup. */
extern void spawn_opposite_offset_effect(DungeonEffect *, s16);
/* sub in spawn_randomized_radial_burst */
extern void select_record_entry_and_value(void *state, void *entries, short index);

#include "dungeon/effect/sprite/directional_entries.h"

/* Functions defined in this translation unit. */
void spawn_randomized_radial_burst(MovingPosition *origin);

#endif
