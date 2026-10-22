#ifndef TOWN_MAP_FORWARD_SURFACE_QUERY_WITH_ARGUMENT_G01117_H
#define TOWN_MAP_FORWARD_SURFACE_QUERY_WITH_ARGUMENT_G01117_H
/* Forward surface query with argument. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01117 - CL:town/func_8008F958, CL:town/func_8008FE64, CL:town/func_80090320, CL:town/func_80090854, CL:town/func_80090D8C, CL:town/func_800912C0, PD:town/engine:800FE480, PD:town/engine:800FE484. */

#include "common.h"
#include "shared/position_views.h"
#include "m2c_compat.h"
#include "shared/game_work.h"

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

typedef struct TargetScratch {
    void *result;
    s16 cell;
    u8 pad06[0x12];
    Vec8 *planes;
    u16 origin_x;
    u16 origin_y;
    u8 pad20[4];
    s32 height;
    s32 best;
    s32 threshold;
    u8 pad30[0x1c];
    u16 x_base;
    u16 y_base;
    u16 x_scan;
    u16 y_scan;
    s32 x_step;
    s32 y_step;
    s32 inner_count;
    s32 outer_count;
    s32 inner_offset;
    s32 outer_offset;
    Quad quad;
} TargetScratch;

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

typedef struct Scratch {
    u8 pad00[4];
    u16 tile;
    u8 pad06[0x12];
    Vec8 * planes;
    s16 x;
    s16 y;
    u8 pad22[4];
    s32 value;
    s32 best;
    s32 limit;
    u8 pad30[0x1C];
    s16 base_x;
    s16 base_y;
    s16 orig_x;
    s16 orig_y;
    s32 step_x;
    s32 step_y;
    s32 inner_count;
    s32 outer_count;
    s32 inner_delta;
    s32 outer_delta;
    Quad quad;
} Scratch;

typedef struct ScratchPrefix {
    u8 pad00[4];
    u16 tile;
    u8 pad06[0x12];
    Vec8 * planes;
    s16 x;
    s16 y;
    u8 pad22[4];
    s32 value;
    s32 best;
    s32 limit;
    u8 pad30[0x1C];
    s16 base_x;
    s16 base_y;
    s16 orig_x;
    s16 orig_y;
    s32 step_x;
    s32 step_y;
    s32 inner_count;
    s32 outer_count;
} ScratchPrefix;

typedef union ScratchArena { Scratch full; ScratchPrefix prefix; } ScratchArena;

typedef struct Scratch80090320 {
    u8 pad00[4];
    u16 tile;
    u8 pad06[0x12];
    u8 * height_data;
    s16 result;
    u16 origin_y;
    u16 origin_z;
    u8 pad22[0xE];
    s32 best;
    s32 lower_bound;
    s32 block_base;
    u8 pad3C[0xC];
    u16 inner_index;
    u8 pad4A[4];
    u16 saved_y;
    u16 start_x;
    u16 start_y;
    s32 x_step;
    s32 y_step;
    s32 inner_count;
    s32 outer_count;
    s32 inner_offset;
    s32 outer_offset;
    s16 d0;
    s16 d1;
    s16 d2;
    s16 d3;
    s16 d4;
    s16 d5;
    s16 d6;
    s16 d7;
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
    s16 tile;
    u8 pad06[0x12];
    Vec_80090854 *planes;
    s16 result;
    s16 x;
    s16 z;
    u8 pad22[0xE];
    s32 best;
    s32 limit;
    s32 block;
    u8 pad3C[0xC];
    s16 inner_bias;
    u8 pad4A[4];
    s16 origin_x;
    s16 scan_x;
    s16 scan_z;
    s32 x_step;
    s32 z_step;
    s32 inner_count;
    s32 outer_count;
    s32 inner_offset;
    s32 outer_offset;
    s16 quad[8];
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
} LowestSurfaceVector;

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
    LowestSurfaceVector *vertices;
    LowestSurfaceVector *planes;
    u8 pad10[4];
    s16 shift;
    u8 pad16[2];
    u16 x_mask;
    u16 y_mask;
} LowestSurfaceMap;

typedef struct {
    u8 pad00[4];
    s16 cell;
    u8 pad06[0x12];
    LowestSurfaceVector *planes;
    s16 x;
    s16 y;
    s16 z;
    u8 pad22[0x1A];
    s32 best;
    s32 lower;
    s32 base_y;
    u8 pad48[2];
    s16 outer_bias;
    s16 base_x;
    u8 pad4E[2];
    s16 scan_x;
    s16 scan_y;
    s32 step_x;
    s32 step_y;
    s32 inner_count;
    s32 outer_count;
    s32 inner_delta;
    s32 outer_delta;
    s16 quad[8];
} LowestSurfaceScratch;

typedef struct {
    u8 pad000[0x1DC];
    LowestSurfaceMap map;
} LowestSurfaceGlobal;

typedef struct Vec_8008EA20 {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vec_8008EA20;

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
    Vec_8008EA20 *vertices;
    Vec_8008EA20 *heights;
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

typedef struct Scratch_8008EA20 {
    u8 pad00[4];
    u16 tile;
    u8 pad06[0x12];
    Vec_8008EA20 *heights;
    s16 x;
    s16 z;
    s16 y;
    u8 pad22[0x1A];
    s32 best;
    s32 limit;
    s32 z_base;
    u8 pad48[2];
    s16 z_offset;
    s16 x_origin;
    u8 pad4E[2];
    s16 x_start;
    s16 z_start;
    s32 x_step;
    s32 z_step;
    s32 x_count;
    s32 z_count;
    s32 x_offset;
    s32 z_offset_acc;
    s16 quad[8];
} Scratch_8008EA20;

extern u8 D_800CFCAC[];
extern GlobalState D_80083160;

/* Shared import declarations; data casts preserve each measured view. */
extern u8 town_map_column_extent[];
extern u8 town_map_row_extent[];
s32 check_scratch_quad_half_turn_gaps(void *scratch);

/* Functions defined in this translation unit. */
s16 forward_surface_query_with_argument(SignedPositionView *record, s32 query_arg);
s16 forward_highest_surface_query(SignedPositionView *record);
s16 forward_smallest_surface_x_query(SignedPositionView *record);
s16 evaluate_surface_components_a(SignedPositionView *components);
s16 evaluate_surface_components_b(SignedPositionView *components);
s16 evaluate_surface_components_c(SignedPositionView *components);
void update_map_world_extents(void);
s32 find_min_qualifying_plane_height(u32 query_x, u32 query_y, s16 query_height, void **plane_out);
s32 find_highest_surface_within_range(s32 world_x, s32 world_y, s16 height);
s16 find_smallest_surface_x_across_tiles(s32 query_x, s32 query_y, s32 query_z);
s32 find_greatest_cell_intersection(s32, s32, s32);
s32 find_lowest_surface_height(s32, s32, s32);
s32 find_highest_valid_cell_height(s32 world_x, s32 world_z, s32 world_y);

#endif
