#ifndef TOWN_MAP_BURST_PARTICLE_BODY_H
#define TOWN_MAP_BURST_PARTICLE_BODY_H

#include "common.h"

/* Body initialized by spawn_burst_particles_around_origin and advanced by its callback. */
typedef struct TownBurstParticleBody {
    u8 pad_00[0xC];
    s16 target_x;
    s16 target_y;
    s16 target_z;
    u8 pad_12[0x36];
    u16 ticks_left;
    u8 pad_4A[2];
    s16 phase;
} TownBurstParticleBody;

#endif
