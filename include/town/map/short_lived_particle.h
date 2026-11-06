#ifndef TOWN_MAP_SHORT_LIVED_PARTICLE_H
#define TOWN_MAP_SHORT_LIVED_PARTICLE_H

#include "common.h"

/* The short-lived object creator installs update_effect_motion_and_fade.
 * Its countdown starts at ten; the cleared phase selects motion before fading. */
typedef struct ShortLivedParticleBody {
    u8 pad_00[0x48];
    s16 remaining_ticks;
    u8 pad_4A[2];
    s16 phase;
} ShortLivedParticleBody;

#endif
