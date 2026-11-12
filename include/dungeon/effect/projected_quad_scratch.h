#ifndef DUNGEON_EFFECT_PROJECTED_QUAD_SCRATCH_H
#define DUNGEON_EFFECT_PROJECTED_QUAD_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"
#include "engine/graphics/sprite_scratch.h"

/* Scratchpad slots of the effect quad renderers that project four world vertices with RotAverage4:
 * the four SVECTOR vertices at +0x64 give the screen XY words at +0xD8 (copied into the packet), the
 * depth cue and flag words at +0x84/+0x88 and the ordering-table index kept at +0xB4; the packet is
 * linked into ordering_table at that index. */
typedef struct ProjectedQuadScratch {
    /* 0x000 */ u8 pad_000[0x18];
    /* 0x018 */ u32 *ordering_table;
    /* 0x01C */ u8 pad_01C[0x48];
    /* 0x064 */ SVECTOR vertices[4];
    /* 0x084 */ s32 depth_cue;
    /* 0x088 */ s32 gte_flag;
    /* 0x08C */ u8 pad_08C[0x28];
    /* 0x0B4 */ u32 ot_index;
    /* 0x0B8 */ u8 pad_0B8[0x20];
    /* 0x0D8 */ SpriteScratchScreenPoint screen[4];
    /* 0x0E8 */ u8 pad_0E8[0x20];
    /* 0x108 */ s32 step_x; /* five-point quads: 16.16 interpolated X and Y steps of the moving edge */
    /* 0x10C */ s32 step_y;
} ProjectedQuadScratch;

#endif
