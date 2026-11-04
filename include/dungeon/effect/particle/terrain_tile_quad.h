#ifndef DUNGEON_EFFECT_PARTICLE_TERRAIN_TILE_QUAD_H
#define DUNGEON_EFFECT_PARTICLE_TERRAIN_TILE_QUAD_H

#include "common.h"

/* Quad body allocated by create_terrain_tile_quad for terrain height rendering. */
typedef struct TerrainTileQuadBody {
    u8 pad_00[0x10];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x1A];
    union { s16 s; u16 u; } unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
} TerrainTileQuadBody;

#endif
