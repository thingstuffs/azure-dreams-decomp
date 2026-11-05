#ifndef DUNGEON_MONSTER_GHOSH_GROWING_PARTICLE_H
#define DUNGEON_MONSTER_GHOSH_GROWING_PARTICLE_H

#include "common.h"

/* Body initialized by create_boss_randomized_effect and advanced by its callback. */
typedef struct GhoshGrowingParticleBody {
    u8 pad_00[0x16];
    u16 remaining_ticks;
    u16 animation_ticks;
    u8 pad_1A[0x3E];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} GhoshGrowingParticleBody;

#endif
