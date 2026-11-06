#ifndef DUNGEON_MONSTER_GLACIER_PROJECTED_DEPTH_H
#define DUNGEON_MONSTER_GLACIER_PROJECTED_DEPTH_H

#include "common.h"
#include "shared/entity.h"

/* update_actor_timed_effects initializes this body and installs
 * apply_relative_projected_depth to track depth against a reference position. */
typedef struct GlacierProjectedDepthBody {
    u8 pad_00[0x1C];
    u16 facing;
    u8 pad_1E[0xA];
    ObjectPosition *reference_position;
} GlacierProjectedDepthBody;

#endif
