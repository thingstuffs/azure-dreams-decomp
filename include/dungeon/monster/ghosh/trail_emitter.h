#ifndef DUNGEON_MONSTER_GHOSH_TRAIL_EMITTER_H
#define DUNGEON_MONSTER_GHOSH_TRAIL_EMITTER_H

#include "common.h"

/* Countdown body shared by the cascading emitter and the rising emitter it spawns.
 * Both creators allocate kind 0x212 and initialize the same two halfwords. */
typedef struct GhoshTrailEmitterBody {
    u8 pad_00[0x16];
    u16 remaining_ticks;
    s16 unk_18;
} GhoshTrailEmitterBody;

#endif
