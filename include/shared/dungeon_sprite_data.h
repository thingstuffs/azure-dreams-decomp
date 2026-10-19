#ifndef SHARED_DUNGEON_SPRITE_DATA_H
#define SHARED_DUNGEON_SPRITE_DATA_H

#include "shared/sprite_source.h"

/* func_8003DB94 indexes entries at eight-byte stride. One caller selects
 * index two; the allocation extent beyond those entries is unproved. */
extern SpriteSourceEntry D_800DE870[];
/* The same selector uses entry zero here; no table extent is claimed. */
extern SpriteSourceEntry D_800DEA68;

#endif
