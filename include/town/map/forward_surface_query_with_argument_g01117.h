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

typedef struct TargetMap {
    u16 *tiles;
    u8 **cells;
    Vec8 *vertices;
    Vec8 *planes;
    u8 pad10[4];
    s16 shift;
    u16 pad16;
    u16 x_mask;
    u16 y_mask;
} TargetMap;

typedef struct TargetGlobal {
    u8 pad000[0x1dc];
    TargetMap map;
} TargetGlobal;

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

typedef struct MapInfo {
    u16 * grid;
    CellRecord **records;
    Vec8 * vertices;
    Vec8 * planes;
    u8 pad10[4];
    s16 shift;
    u8 pad16[2];
    u16 x_mask;
    u16 y_mask;
} MapInfo;

typedef struct GlobalState { u8 pad000[0x1DC]; MapInfo map; } GlobalState;

/* The Y and Z offsets of each corner from the X-intersection query point. */
typedef struct MapSurfaceYZOffset {
    s16 y;
    s16 z;
} MapSurfaceYZOffset;

typedef struct Scratch80090320 {
    u8 pad00[4];
    MapSurfaceCell lookup;
    u8 * height_data;
    MapSurfaceXQuery query;
    MapSurfaceScan scan;
    MapSurfaceYZOffset quad[4];
} Scratch80090320;

typedef struct Grid80090320 {
    u16 * occupancy;
    u8 **entries;
    u8 * vertices;
    u8 * height_data;
    u8 pad10[4];
    s16 shift;
    u16 pad16;
    u16 x_mask;
    u16 y_mask;
} Grid80090320;

typedef struct S_8008DA80_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x8];
    u16 unk_10;
    u8 pad_12[0x4];
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_16;   /* overlapping accesses */
} S_8008DA80_1;

/* entry in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_2 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_8008DA80_2;

/* plane in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_8008DA80_3;

/* vertex in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_4 {
    s16 unk_00;
} S_8008DA80_4;

/* ((S_8008DA80_1 *)entry)->unk_10 * 8 + scratch->height_data in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_5;

/* ((S_8008DA80_1 *)entry)->unk_00 * 8 + vertices in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_6;

/* ((S_8008DA80_1 *)entry)->unk_02 * 8 + vertices in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_7;

/* ((S_8008DA80_1 *)entry)->unk_06 * 8 + vertices in find_smallest_surface_x_across_tiles */
typedef struct S_8008DA80_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_8008DA80_8;

typedef struct Vec_80090854 {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vec_80090854;

typedef struct Cell_80090854 {
    u16 v0;
    u16 v2;
    u16 v4;
    u16 v6;
    u8 pad08[8];
    u16 plane;
    u8 pad12[4];
    u16 flags;
} Cell_80090854;

typedef struct Map_80090854 {
    u16 *tiles;
    Cell_80090854 **cells;
    Vec_80090854 *vertices;
    Vec_80090854 *planes;
    u8 pad10[4];
    s16 shift;
    u16 pad16;
    u16 x_mask;
    u16 z_mask;
} Map_80090854;

typedef struct Scratch_80090854 {
    u8 pad00[4];
    MapSurfaceCell lookup;
    Vec_80090854 *planes;
    MapSurfaceXQuery query;
    MapSurfaceScan scan;
    MapSurfaceYZOffset quad[4];
} Scratch_80090854;

typedef struct Global_80090854 {
    u8 pad000[0x1DC];
    Map_80090854 map;
} Global_80090854;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} MapSurfaceHeightVector;

typedef struct {
    u16 vertex0;
    u16 vertex2;
    u16 vertex4;
    u16 vertex6;
    u8 pad08[8];
    u16 plane;
    u8 pad12[4];
    u16 flags;
} LowestSurfaceCell;

typedef struct {
    u16 *grid;
    LowestSurfaceCell **records;
    MapSurfaceHeightVector *vertices;
    MapSurfaceHeightVector *planes;
    u8 pad10[4];
    s16 shift;
    u8 pad16[2];
    u16 x_mask;
    u16 y_mask;
} LowestSurfaceMap;

typedef struct MapSurfaceHeightScratch {
    u8 pad00[4];
    MapSurfaceCell lookup;
    MapSurfaceHeightVector *planes;
    s16 x;
    s16 height;
    s16 z;
    u8 pad22[0x1A];
    MapSurfaceSearchRange height_range;
    u8 pad48[2];
    s16 outer_offset;
    s16 base_x;
    u8 pad4E[2];
    MapSurfaceScan scan;
    s16 quad[8];
} MapSurfaceHeightScratch;

typedef struct {
    u8 pad000[0x1DC];
    LowestSurfaceMap map;
} LowestSurfaceGlobal;

typedef struct Cell_8008EA20 {
    u16 v0;
    u16 v1;
    u16 v3;
    u16 v2;
    u8 pad08[8];
    u16 height_index;
    u8 pad12[4];
    u16 flags;
} Cell_8008EA20;

typedef struct Map_8008EA20 {
    u16 *tiles;
    Cell_8008EA20 **cells;
    MapSurfaceHeightVector *vertices;
    MapSurfaceHeightVector *heights;
    u8 pad10[4];
    s16 shift;
    u16 pad16;
    u16 x_mask;
    u16 z_mask;
} Map_8008EA20;

typedef struct Global_8008EA20 {
    u8 pad000[0x1DC];
    Map_8008EA20 map;
} Global_8008EA20;

extern u8 D_800CFCAC[];
extern GlobalState D_80083160;

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
