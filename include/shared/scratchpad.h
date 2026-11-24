#ifndef SHARED_SCRATCHPAD_H
#define SHARED_SCRATCHPAD_H
#include "common.h"
/* PS1 1 KB scratchpad RAM at 0x1F800000. Halfword and word accesses
 * address the same storage; the base remains explicit at each caller. */
typedef union ScratchPad { u8 b[0x400]; s8 sb[0x400]; u16 h[0x200]; s16 sh[0x200]; u32 w[0x100]; s32 sw[0x100]; } ScratchPad;

/* Exact access views shared across registered binary consumers. */
/* Unsigned halfword access within the renderer scratchpad; two-byte extent. */
typedef struct ScratchUnsignedHalf { unsigned short v; } ScratchUnsignedHalf;

/* Corner angles and the half-turn gaps between consecutive angles. */
typedef struct ScratchQuadTurnOutput {
    /* 0x000 */ s32 angles[4]; /* ratan2 results; slots 1 to 3 are overwritten with deltas */
    /* 0x010 */ u8 pad_10[4];
    /* 0x014 */ s32 gaps[3];
} ScratchQuadTurnOutput;

/* Coordinates, height bounds and cell position for one terrain surface query. */
typedef struct TerrainQueryFields {
    /* 0x000 */ u16 query_x; /* query X within the tile */
    /* 0x002 */ u16 query_y; /* query Y within the tile */
    /* 0x004 */ s32 candidate_height;
    /* 0x008 */ s32 best_height; /* lowest qualifying height, initialized to 0x400 */
    /* 0x00C */ s32 limit; /* minimum accepted height */
    /* 0x010 */ u16 cell_index; /* linear map cell index */
    /* 0x012 */ s16 face_offset; /* negated cell height offset */
} TerrainQueryFields;

#endif
