#ifndef DUNGEON_EFFECT_COLORED_POINT_SCRATCH_H
#define DUNGEON_EFFECT_COLORED_POINT_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"

/* Scratchpad slots of the colored point renderers. RotTransPers projects the point position into a
 * one-pixel TILE_1 packet and writes its depth cue and flag words here; the TILE_1 and the DR_MODE that
 * follows it are taken from the draw context's packet cursor (copied here for the walk and stored back
 * at the end) and linked into ordering_table at ot_index. */
typedef struct ColoredPointScratch {
    /* 0x00 */ SVECTOR position;
    /* 0x08 */ u8 pad_08[0x10];
    /* 0x18 */ void *packet_cursor;
    /* 0x1C */ u8 pad_1C[4];
    /* 0x20 */ u32 *ordering_table;
    /* 0x24 */ u8 pad_24[0x6C];
    /* 0x90 */ s32 depth_cue;
    /* 0x94 */ s32 gte_flag;
    /* 0x98 */ u8 pad_98[0x28];
    /* 0xC0 */ u32 ot_index;
} ColoredPointScratch;

#endif
