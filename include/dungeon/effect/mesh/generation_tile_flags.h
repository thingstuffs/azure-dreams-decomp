#ifndef DUNGEON_EFFECT_MESH_GENERATION_TILE_FLAGS_H
#define DUNGEON_EFFECT_MESH_GENERATION_TILE_FLAGS_H
#include "common.h"

/* Partial cell view used by the perpendicular-tile effect. */
typedef struct {
    u8 pad[4];
    u16 flags;
} DungeonTile;

extern DungeonTile generation_cells[2];

#endif
