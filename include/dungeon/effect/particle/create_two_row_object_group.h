/* Complete resident-engine cohort contract. Review pending. */
#ifndef DUNGEON_ENGINE_PARTICLE_EFFECTS_H
#define DUNGEON_ENGINE_PARTICLE_EFFECTS_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

/* Spawned by spawn_scattered_timed_objects and advanced by its node callback. */
typedef struct ScatteredTimedEffectBody {
    u8 pad_00[0x10];
    s16 landing_height;
    u8 pad_12[0x36];
    u16 ticks_left;
    u8 pad_4A[0x2];
    s16 phase;
} ScatteredTimedEffectBody;

/* Retail allocator return and flag word; identical to the incoming shared declaration. */
void *allocate_flagged_object_node(int flags);

/* Shared packed-vertex projection record. */
void transform_rotated_vertices(void *transform_data);

#endif
