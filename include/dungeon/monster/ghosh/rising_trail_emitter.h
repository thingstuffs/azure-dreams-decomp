#ifndef DUNGEON_MONSTER_GHOSH_RISING_TRAIL_EMITTER_H
#define DUNGEON_MONSTER_GHOSH_RISING_TRAIL_EMITTER_H

#include "common.h"

/* spawn_rising_trail_emitter allocates this body and installs its countdown callback. */
typedef struct GhoshRisingTrailEmitterBody {
    u8 pad_00[0x16];
    u16 remaining_ticks;
    s16 unk_18;
} GhoshRisingTrailEmitterBody;

#endif
