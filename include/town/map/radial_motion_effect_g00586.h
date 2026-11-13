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
#include "engine/node.h"

/* arg0 in create_reverse_motion_effect */

/* arg0 in spawn_radial_effect_objects */
typedef struct S_800A895C_1 {
    union { u16 u16; s32 s32; } unk_00;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_04;   /* accessed as both */
    union { u16 u16; s32 s32; } unk_08;   /* accessed as both */
} S_800A895C_1;

/* arg1 in spawn_radial_effect_objects */
/* object in spawn_radial_effect_objects */

typedef struct StackRecord {
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

/* extern */

#include "town/map/map_animation_entries.h"
#include "town/map/motion.h"
#include "sdk/libgte.h"
#include "sdk/rand.h"


/* Functions defined in this translation unit. */
void *create_reverse_motion_effect(StackRecord *source_motion, u32 flags);

#endif
