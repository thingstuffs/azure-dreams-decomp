#ifndef DUNGEON_MONSTER_GHOSH_TRACKED_FADE_H
#define DUNGEON_MONSTER_GHOSH_TRACKED_FADE_H

#include "common.h"

/* create_boss_linked_effect installs update_boss_effect_growth for this body.
 * The callback brightens the sprite, tracks the supplied position, then fades it. */
typedef struct GhoshTrackedFadeBody {
    u8 pad_00[0x12];
    u16 phase;
    u8 pad_14[2];
    u16 phase_ticks;
    s16 phase_duration;
    u8 pad_1A[6];
    void *owner;
    void *source_position; /* MovingPosition supplied by the creator. */
} GhoshTrackedFadeBody;

#endif
