#ifndef TOWN_MINIGAME_BRIEF_RANDOM_PARTICLE_BODY_H
#define TOWN_MINIGAME_BRIEF_RANDOM_PARTICLE_BODY_H

#include "common.h"

/* create_brief_randomized_particle stores the timer in a node body and
 * installs the 80026B00 timeout callback that decrements the same field. */
typedef struct BriefRandomParticleBody {
    u8 pad_00[0xE];
    u16 ticks_left;
} BriefRandomParticleBody;

#endif
