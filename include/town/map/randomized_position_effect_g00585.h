#ifndef TOWN_MAP_RANDOMIZED_POSITION_EFFECT_G00585_H
#define TOWN_MAP_RANDOMIZED_POSITION_EFFECT_G00585_H
/* Randomized position effect shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AAD70. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"

#ifndef NULL
#define NULL 0
#endif

struct Dst;

struct Elem;

/* arg0 in create_randomized_position_effect */
typedef struct S_800A84D0_4 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800A84D0_4;

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
    u8 padC[10];
    s16 unk16;
} LocalRecord;

void select_record_entry_and_value(void *state,void *entries, short index);

void fade_timed_primitive(void *record_fields, void *unused, SpriteFrameState *primitive);
extern s32 radial_sprite_entries;
extern s32 rand(void);

u32 scale_random_to_unsigned_halfword_limit(s32 limit);

/* Functions defined in this translation unit. */
void *create_randomized_position_effect(MovingPosition *source_position);
void build_randomized_offset_records(void *origin, void *spread, s32 count);

#endif
