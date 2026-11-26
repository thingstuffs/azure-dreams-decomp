#ifndef TOWN_MAP_FORWARD_SURFACE_QUERY_WITH_ARGUMENT_G01117_H
#define TOWN_MAP_FORWARD_SURFACE_QUERY_WITH_ARGUMENT_G01117_H
/* Forward surface query with argument. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_8008F958, CL:town/func_8008FE64, CL:town/func_80090320, CL:town/func_80090854, CL:town/func_80090D8C, CL:town/func_800912C0, PD:town/engine:800FE480, PD:town/engine:800FE484. */

#include "common.h"
#include "shared/position_views.h"
#include "m2c_compat.h"
#include "shared/game_work.h"

/* Cell index used to look up the query tile. */
typedef struct MapSurfaceCell {
    s16 index;
    u8 pad_02[0x12];
} MapSurfaceCell;

/* Coordinates, steps, counters and offsets for a two-by-two surface search. */
typedef struct MapSurfaceScan {
    /* 0x000 */ u16 start_column;
    /* 0x002 */ u16 start_row;
    /* 0x004 */ s32 x_step;
    /* 0x008 */ s32 y_step;
    /* 0x00C */ s32 inner_count;
    /* 0x010 */ s32 outer_count;
    /* 0x014 */ s32 inner_offset;
    /* 0x018 */ s32 outer_offset;
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

/* Search range and the column displacement added to each intersection. */
typedef struct MapSurfaceXSearch {
    MapSurfaceSearchRange range;
    u8 pad_0C[0x0C];
    u16 inner_offset;
} MapSurfaceXSearch;

/* Query coordinates, intersection result and bounds for an X-axis search. */
typedef struct MapSurfaceXQuery {
    s16 result;
    u16 y;
    u16 z;
    u8 pad_06[0x0E];
    MapSurfaceXSearch search;
    u8 pad_30[2];
    u16 base_y;
} MapSurfaceXQuery;

typedef struct {
    s8 pad[0x14];
    s16 unk14;
    s16 unk16;
} TownViewState;

typedef struct Vec8 {
    u32 xy;
    s16 z;
    s16 pad;
} Vec8;

typedef union Quad {
    u32 words[4];
    u16 halves[8];
    s16 vals[8];
} Quad;

typedef struct MapSurfacePlaneScratch {
    void *result;
    MapSurfaceCell lookup;
    Vec8 *planes;
    s16 x;
    s16 y;
    u8 pad20[4];
    MapSurfacePlaneRange plane_range;
    u8 pad30[0x1c];
    u16 base_x;
    u16 base_y;
    MapSurfaceScan scan;
    Quad quad;
} MapSurfacePlaneScratch;

struct ScratchQuad;



typedef struct CellRecord {
    u16 v0;
    u16 v2;
    u16 v4;
    u16 v6;
    u16 v8;
    u8 pad0A;
    u8 edge_flags;
    u8 pad0C[0x0B];
    u8 flags;
} CellRecord;

/* The Y and Z offsets of each corner from the X-intersection query point. */
typedef struct MapSurfaceYZOffset {
    s16 y;
    s16 z;
} MapSurfaceYZOffset;

/* Signed components shared by side and height searches over the indexed surface map. */
typedef struct TownMapVector {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} TownMapVector;

typedef struct TownIndexedSurfaceCell {
    u16 v0;
    u16 v2;
    u16 v4;
    u16 v6;
    u8 pad08[8];
    u16 plane;
    u8 pad12[4];
    u16 flags;
} TownIndexedSurfaceCell;

typedef struct MapSurfaceXScratch {
    u8 pad00[4];
    MapSurfaceCell lookup;
    TownMapVector *planes;
    MapSurfaceXQuery query;
    MapSurfaceScan scan;
    MapSurfaceYZOffset quad[4];
} MapSurfaceXScratch;

typedef struct MapSurfaceHeightScratch {
    u8 pad00[4];
    MapSurfaceCell lookup;
    TownMapVector *planes;
    s16 query_x;
    s16 candidate_height;
    s16 query_z;
    u8 pad22[0x1A];
    MapSurfaceSearchRange height_range;
    u8 pad48[2];
    s16 cell_row_offset;
    s16 tile_query_x;
    u8 pad4E[2];
    MapSurfaceScan scan;
    s16 quad[8];
} MapSurfaceHeightScratch;

extern u8 D_800CFCAC[];

/* Shared import declarations; data casts preserve each measured view. */
extern s32 town_map_column_extent;
extern s32 town_map_row_extent;
s32 check_scratch_quad_half_turn_gaps(void *scratch);

/* Functions defined in this translation unit. */
s16 find_min_qualifying_plane_height_at(SignedPositionView *record, void **plane_out);
s16 find_highest_surface_within_range_at(SignedPositionView *record);
s16 find_smallest_surface_x_at(SignedPositionView *record);
s16 find_greatest_cell_intersection_at(SignedPositionView *components);
s16 find_lowest_surface_height_at(SignedPositionView *components);
s16 find_highest_valid_cell_height_at(SignedPositionView *components);
void update_map_world_extents(void);
s32 find_min_qualifying_plane_height(u32 query_x, u32 query_y, s16 query_height, void **plane_out);
s32 find_highest_surface_within_range(s32 world_x, s32 world_y, s16 height);
s16 find_smallest_surface_x_across_tiles(s32 query_x, s32 query_y, s32 query_z);
s32 find_greatest_cell_intersection(s32, s32, s32);
s32 find_lowest_surface_height(s32, s32, s32);
s32 find_highest_valid_cell_height(s32 world_x, s32 world_z, s32 world_y);

#endif
