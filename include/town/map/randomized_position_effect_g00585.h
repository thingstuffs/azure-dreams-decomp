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

#ifndef NULL
#define NULL 0
#endif

struct Dst;

struct Elem;

typedef struct S_800A84D0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
} S_800A84D0_0;

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

void func_8003DB94(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node();
void fade_timed_primitive(void *record_fields, void *unused, SpriteFrameState *primitive);
extern s32 D_800D1464;
extern s32 rand(void);

u32 scale_random_to_unsigned_halfword_limit(s32 limit);

/* Functions defined in this translation unit. */
void *create_randomized_position_effect(MovingPosition *source_position);
void build_randomized_offset_records(void *origin, void *spread, s32 count);

#endif
