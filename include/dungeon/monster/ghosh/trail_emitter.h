#ifndef DUNGEON_MONSTER_GHOSH_TRAIL_EMITTER_H
#define DUNGEON_MONSTER_GHOSH_TRAIL_EMITTER_H

#include "common.h"

/* Body allocated by spawn_cascading_trail_emitter and advanced by its callback. */
typedef struct GhoshTrailEmitterBody {
    u8 pad_00[0x16];
    u16 remaining_ticks;
    s16 unk_18;
} GhoshTrailEmitterBody;

#endif
