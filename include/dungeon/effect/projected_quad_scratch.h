#ifndef DUNGEON_EFFECT_PROJECTED_QUAD_SCRATCH_H
#define DUNGEON_EFFECT_PROJECTED_QUAD_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"
#include "engine/graphics/sprite_scratch.h"

/* Scratchpad slots of the effect renderers that project two to four world vertices with RotTransPers,
 * RotAverage3 or RotAverage4: the SVECTOR vertices at +0x64 give the screen XY words at +0xD8 (copied into the packet),
 * the depth cue and flag words at +0x84/+0x88 and the ordering-table index kept at +0xB4; the line renderers keep the
 * two endpoint depths and average them into ot_index. The packet is linked into ordering_table at that index. */
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
    /* 0x0E8 */ u8 pad_0E8[0xC];
    /* 0x0F4 */ s32 start_depth; /* RotTransPers return for the first endpoint of the line renderers */
    /* 0x0F8 */ s32 end_depth;
    /* 0x0FC */ u8 pad_0FC[0xC];
    /* 0x108 */ s32 step_x; /* 16.16 interpolation steps of the moving edge */
    /* 0x10C */ s32 step_y;
    /* 0x110 */ s32 step_z;
} ProjectedQuadScratch;
#define PROJECTED_QUAD_SCRATCH ((ProjectedQuadScratch *)0x1F800000)

#endif
