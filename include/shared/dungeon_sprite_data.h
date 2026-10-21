#ifndef SHARED_DUNGEON_SPRITE_DATA_H
#define SHARED_DUNGEON_SPRITE_DATA_H

#include "shared/sprite_source.h"

/* func_8003DB94 indexes entries at eight-byte stride. One caller selects
 * index two; the allocation extent beyond those entries is unproved. */
extern SpriteSourceEntry effect_sprite_sources[];
/* The same selector uses entry zero here; no table extent is claimed. */
extern SpriteSourceEntry secondary_sprite;

#endif
