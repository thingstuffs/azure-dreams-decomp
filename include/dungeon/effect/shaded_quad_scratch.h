#ifndef DUNGEON_EFFECT_SHADED_QUAD_SCRATCH_H
#define DUNGEON_EFFECT_SHADED_QUAD_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"

/* Scratchpad slots of the shaded effect quad renderers. RotMatrix turns the angles into the local
 * matrix, whose translation is the effect position; CompMatrix composes it with the current GTE
 * matrix, ScaleMatrix applies the scale, and RotAverage4 projects the four vertices into the
 * packet (POLY_F4, POLY_G4 or, with the texture words, POLY_GT4), writing its depth cue and flag words here. The packet is linked into
 * ordering_table at ot_index. */
typedef struct ShadedQuadScratch {
    /* 0x000 */ u8 pad_000[0xC];
    /* 0x00C */ s32 uv_u_start; /* textured variants: texture u/v start and extent words */
    /* 0x010 */ s32 uv_v_start;
    /* 0x014 */ s32 uv_u_extent;
    /* 0x018 */ s32 uv_v_extent;
    /* 0x01C */ u8 pad_01C[8];
    /* 0x024 */ u32 *ordering_table;
    /* 0x028 */ u16 render_flags;
    /* 0x02A */ u8 pad_02A[0xA];
    /* 0x034 */ VECTOR scale;
    /* 0x044 */ u8 pad_044[0x10];
    /* 0x054 */ MATRIX composed_matrix;
    /* 0x074 */ MATRIX local_matrix;
    /* 0x094 */ u8 pad_094[0x10];
    /* 0x0A4 */ SVECTOR angles;
    /* 0x0AC */ u8 pad_0AC[4];
    /* 0x0B0 */ SVECTOR vertices[4];
    /* 0x0D0 */ s32 depth_cue;
    /* 0x0D4 */ s32 gte_flag;
    /* 0x0D8 */ u8 pad_0D8[0x28];
    /* 0x100 */ s32 ot_index;
} ShadedQuadScratch;

#endif
