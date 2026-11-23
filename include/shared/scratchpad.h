#ifndef SHARED_SCRATCHPAD_H
#define SHARED_SCRATCHPAD_H
#include "common.h"
/* PS1 1 KB scratchpad RAM at 0x1F800000. Halfword and word accesses
 * address the same storage; the base remains explicit at each caller. */
typedef union ScratchPad { u8 b[0x400]; s8 sb[0x400]; u16 h[0x200]; s16 sh[0x200]; u32 w[0x100]; s32 sw[0x100]; } ScratchPad;

/* Exact access views shared across registered binary consumers. */
/* Unsigned halfword access within the renderer scratchpad; two-byte extent. */
typedef struct ScratchUnsignedHalf { unsigned short v; } ScratchUnsignedHalf;

/* One quad corner relative to the query point. */
typedef struct ScratchQuadCorner {
    s16 x;
    s16 z;
} ScratchQuadCorner;

/* Corner angles and the half-turn gaps between consecutive angles. */
typedef struct ScratchQuadTurnOutput {
    /* 0x000 */ s32 angles[4]; /* ratan2 results; slots 1 to 3 are overwritten with deltas */
    /* 0x010 */ u8 pad_10[4];
    /* 0x014 */ s32 gaps[3];
} ScratchQuadTurnOutput;

/* Quad-turn inputs and outputs at scratchpad +0x6C (town map surface finders) and TerrainQueryScratch +0x154. */
typedef struct ScratchQuadTurn {
    /* 0x000 */ ScratchQuadCorner corners[4];
    /* 0x010 */ ScratchQuadTurnOutput output;
} ScratchQuadTurn;

/* Starting map coordinates before applying the scan offsets. */
typedef struct MapSurfaceScanStart {
    u16 column;
    u16 row;
} MapSurfaceScanStart;

/* Steps, counters and offsets for a two-by-two map surface search. */
typedef struct MapSurfaceScan {
    /* 0x000 */ s32 x_step;
    /* 0x004 */ s32 y_step;
    /* 0x008 */ s32 inner_count;
    /* 0x00C */ s32 outer_count;
    /* 0x010 */ s32 inner_offset;
    /* 0x014 */ s32 outer_offset;
} MapSurfaceScan;

/* Candidate plane height, best accepted height and threshold. */
typedef struct MapSurfacePlaneRange {
    s32 candidate;
    s32 best;
    s32 threshold;
} MapSurfacePlaneRange;

/* Best eligible value, query bound and aligned base for one axis. */
typedef struct MapSurfaceSearchRange {
    /* 0x000 */ s32 best;
    /* 0x004 */ s32 bound;
    /* 0x008 */ s32 base;
} MapSurfaceSearchRange;

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

/* Scratchpad block of the terrain surface queries, above the renderer slots (+0x140): the query entries
 * write the cell corners into quad_turn and is_point_in_quad reads them. */
typedef struct TerrainQueryScratch {
    /* 0x000 */ u8 pad_000[0x140];
    /* 0x140 */ TerrainQueryFields query;
    /* 0x154 */ ScratchQuadTurn quad_turn; /* is_point_in_quad input */
} TerrainQueryScratch;
#define TERRAIN_QUERY_SCRATCH ((TerrainQueryScratch *)0x1F800000)

#endif
