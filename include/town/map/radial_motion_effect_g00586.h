#ifndef TOWN_MAP_RADIAL_MOTION_EFFECT_G00586_H
#define TOWN_MAP_RADIAL_MOTION_EFFECT_G00586_H
/* Radial motion effect shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AB02C. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_payload.h"

typedef struct S_800A878C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800A878C_2;

/* arg0 in create_reverse_motion_effect */
typedef struct S_800A878C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    s32 unk_04;
} S_800A878C_4;

/* arg0 in spawn_radial_effect_objects */
typedef struct S_800A895C_1 {
    union { u16 u16; s32 s32; } unk_00;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_04;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_08;   /* accessed as both */
} S_800A895C_1;

/* arg1 in spawn_radial_effect_objects */
/* object in spawn_radial_effect_objects */

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

/* extern */
void select_record_entry_and_value(void *state,void *entries, short index);
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
/* extern */
extern void D_800A86BC();
#include "shared/sprite_source.h"
extern SpriteSourceEntry map_animation_sprite_entries[];
extern s32 rsin(s32 value);
extern s32 rcos(s32 value);

u32 scale_random_to_unsigned_halfword_limit(s32 limit);
s32 rand(void);

/* Functions defined in this translation unit. */
void *create_reverse_motion_effect(S_800A878C_2 *source_motion, u32 flags);
void spawn_radial_effect_objects(MovingPosition *center, S_800A895C_1 *spread, s32 count);

#endif
