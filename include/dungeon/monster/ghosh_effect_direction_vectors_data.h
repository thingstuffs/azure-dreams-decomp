#ifndef DUNGEON_MONSTER_GHOSH_EFFECT_DIRECTION_VECTORS_DATA_H
#define DUNGEON_MONSTER_GHOSH_EFFECT_DIRECTION_VECTORS_DATA_H

#include "common.h"

/* Eight 4-byte direction pairs copied from the Ghosh overlay table. */
typedef struct {
    s16 x;
    u16 y;
} GhoshEffectDirectionPair;

typedef struct {
    GhoshEffectDirectionPair pair[8];
} __attribute__((packed)) GhoshEffectDirectionTable;

extern GhoshEffectDirectionTable ghosh_effect_direction_vectors;

#endif
