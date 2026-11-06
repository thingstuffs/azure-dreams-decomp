#ifndef DUNGEON_ITEM_CONVERGING_COLOR_PARTICLE_H
#define DUNGEON_ITEM_CONVERGING_COLOR_PARTICLE_H

#include "common.h"
#include "shared/entity.h"

/* Body shared by create_converging_color_particle and its installed updater. */
typedef struct ConvergingColorParticleBody {
    void *channel_source;
    ObjectPosition *target_position;
    u8 pad_08[4];
    s16 steps_left;
} ConvergingColorParticleBody;

#endif
