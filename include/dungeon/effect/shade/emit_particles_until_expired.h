#ifndef DUNGEON_EFFECT_SHADE_EMIT_PARTICLES_UNTIL_EXPIRED_H
#define DUNGEON_EFFECT_SHADE_EMIT_PARTICLES_UNTIL_EXPIRED_H

#include "common.h"

/* Color and lifetime state for particles emitted by the timed emitter. */
typedef struct EmitParticlesUntilExpiredBody {
    u8 pad_00[0xC];
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_0F[0xF];
    s16 remaining_ticks;
    s16 initial_ticks;
} EmitParticlesUntilExpiredBody;

#endif
