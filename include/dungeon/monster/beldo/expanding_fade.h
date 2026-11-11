#ifndef DUNGEON_MONSTER_BELDO_EXPANDING_FADE_H
#define DUNGEON_MONSTER_BELDO_EXPANDING_FADE_H

#include "common.h"
#include "shared/dungeon_moving_views.h"

/* create_effect_from_sprite_and_facing initializes this body and installs
 * expand_fade_effect_and_expire, which tracks the source, expands, and fades. */
typedef struct BeldoExpandingFadeBody {
    u8 pad_00[0x96];
    u16 ticks_left;
    u8 pad_98[0x10];
    s16 duration;
    u8 pad_AA[2];
    struct ObjectPosition *source_position;
} BeldoExpandingFadeBody;

#endif
