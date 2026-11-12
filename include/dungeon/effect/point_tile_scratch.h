#ifndef DUNGEON_EFFECT_POINT_TILE_SCRATCH_H
#define DUNGEON_EFFECT_POINT_TILE_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"

/* Scratchpad slots of the monster point-tile renderers (Death, Metal and Saber). RotTransPers projects
 * each linked point's position into a one-pixel TILE_1 packet and writes its depth cue and flag words
 * here; the TILE_1 and the DR_MODE after it are taken from packet_cursor (the draw context's packet
 * cursor, copied here for the walk and stored back at the end) and linked into ordering_table at
 * ot_index. */
typedef struct PointTileScratch {
    /* 0x000 */ u8 pad_000[4];
    /* 0x004 */ SVECTOR position;
    /* 0x00C */ u8 pad_00C[0x10];
    /* 0x01C */ void *packet_cursor;
    /* 0x020 */ u8 pad_020[4];
    /* 0x024 */ u32 *ordering_table;
    /* 0x028 */ u8 pad_028[0xA8];
    /* 0x0D0 */ s32 depth_cue;
    /* 0x0D4 */ s32 gte_flag;
    /* 0x0D8 */ u8 pad_0D8[0x28];
    /* 0x100 */ s32 ot_index;
} PointTileScratch;

#endif
