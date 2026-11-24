#ifndef DUNGEON_EFFECT_SHADED_QUAD_SCRATCH_H
#define DUNGEON_EFFECT_SHADED_QUAD_SCRATCH_H

#include "common.h"
#include "sdk/libgte_matrix.h"
#include "engine/graphics/sprite_scratch.h"

/* Scratchpad slots of the shaded effect quad renderers. RotMatrix turns the angles into the local
 * matrix, whose translation is the effect position; CompMatrix composes it with the current GTE
 * matrix, ScaleMatrix applies the scale, and RotAverage4 projects the four vertices into the
 * packet (POLY_F4, POLY_G4 or, with the texture words, POLY_GT4), writing its depth cue and flag words here. The point renderers
 * project position instead. The packet is linked into ordering_table at ot_index. */
typedef struct ShadedQuadScratch {
    /* 0x000 */ u8 pad_000[4];
    /* 0x004 */ SVECTOR position; /* RotTransPers input of the point renderers */
    /* 0x00C */ s32 uv_u_start;
    /* 0x010 */ s32 uv_v_start;
    /* 0x014 */ s32 uv_u_extent;
    /* 0x018 */ s32 uv_v_extent;
    /* 0x01C */ void *packet_cursor;
    /* 0x020 */ u8 pad_020[4];
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
    /* 0x0D8 */ u8 pad_0D8[0x20];
    /* 0x0F8 */ SpriteScratchScreenPoint screen_origin; /* project_sprite_entries_to_quads */
    /* 0x0FC */ u8 pad_0FC[4];
    /* 0x100 */ s32 ot_index;
} ShadedQuadScratch;
#define SHADED_QUAD_SCRATCH ((ShadedQuadScratch *)0x1F800000)

/* The linked fragment renderers copy each packed XY word and Z halfword into an
 * eight-byte GTE input, then queue the projected packet by its biased depth. */
typedef struct PackedQuadVertex {
    s32 xy;
    s16 z;
    u8 pad_06[2];
} PackedQuadVertex;

typedef struct PackedShadedQuadScratch {
    /* 0x000 */ u8 pad_000[0x18];
    /* 0x018 */ void *packet_cursor;
    /* 0x01C */ u8 pad_01C[4];
    /* 0x020 */ u8 *ordering_table;
    /* 0x024 */ u8 pad_024[0x4C];
    /* 0x070 */ PackedQuadVertex vertices[4];
    /* 0x090 */ s32 depth_cue;
    /* 0x094 */ s32 gte_flag;
    /* 0x098 */ u8 pad_098[0x28];
    /* 0x0C0 */ u32 ot_index;
} PackedShadedQuadScratch;
#define PACKED_SHADED_QUAD_SCRATCH ((PackedShadedQuadScratch *)0x1F800000)

#endif
