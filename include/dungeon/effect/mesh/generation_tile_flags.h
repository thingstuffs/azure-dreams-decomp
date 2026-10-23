#ifndef DUNGEON_EFFECT_MESH_GENERATION_TILE_FLAGS_H
#define DUNGEON_EFFECT_MESH_GENERATION_TILE_FLAGS_H
#include "common.h"

/* Partial cell view used by the perpendicular-tile effect. */
typedef struct {
    u8 pad[4];
    u16 flags;
} DungeonTile;

/* clear_generation_cell_grid resets 0x1000 six-byte cells (64 by 64). */
extern DungeonTile generation_cells[4096];

#endif
