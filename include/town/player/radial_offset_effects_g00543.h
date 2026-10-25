#ifndef TOWN_PLAYER_RADIAL_OFFSET_EFFECTS_G00543_H
#define TOWN_PLAYER_RADIAL_OFFSET_EFFECTS_G00543_H
/* Create randomized radial offset effects (G00543). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A1CC. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_payload.h"

#ifndef NULL
#define NULL 0
#endif

struct Dst;

struct Elem;

typedef struct S_8009792C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_8009792C_2;

/* arg0 in spawn_radial_objects */
typedef struct S_80097AD0_1 {
    union { u16 u16; s32 s32; } unk_00;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_04;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_08;   /* accessed as both */
} S_80097AD0_1;

/* arg1 in spawn_radial_objects */
/* object in spawn_radial_objects */

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 z;
    s16 unk8;
    u16 y;
    s32 fieldC;
    s32 field10;
    s16 unk14;
    s16 field16;
} StackRecord;

void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 town_radial_offset_callback;
extern s32 radial_sprite_entries;
extern s32 rsin(s32 value);
extern s32 rcos(s32 value);

extern u32 scale_random_to_unsigned_halfword_limit(s32 limit);
extern s32 rand(void);

/* Functions defined in this translation unit. */
void *create_randomized_offset_effect(S_8009792C_2 *source, u32 angle);
void spawn_radial_objects(MovingPosition *origin, S_80097AD0_1 *spread, s32 count);

#endif
