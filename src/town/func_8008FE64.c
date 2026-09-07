#include "common.h"

typedef struct Vec8 { u32 xy; s16 z; s16 pad; } Vec8;
typedef union Quad { u32 words[4]; s16 vals[8]; } Quad;
typedef struct CellRecord {
    u16 v0; u16 v2; u16 v4; u16 v6; u16 v8;
    u8 pad0A; u8 edge_flags; u8 pad0C[0x0B]; u8 flags;
} CellRecord;
typedef struct MapInfo {
    u16 *grid; CellRecord **records; Vec8 *vertices; Vec8 *planes;
    u8 pad10[4]; s16 shift; u8 pad16[2]; u16 x_mask; u16 y_mask;
} MapInfo;
typedef struct GlobalState { u8 pad000[0x1DC]; MapInfo map; } GlobalState;
typedef struct Scratch {
    u8 pad00[4]; u16 tile; u8 pad06[0x12]; Vec8 *planes; s16 x; s16 y;
    u8 pad22[4]; s32 value; s32 best; s32 limit; u8 pad30[0x1C];
    s16 base_x; s16 base_y; s16 orig_x; s16 orig_y;
    s32 step_x; s32 step_y; s32 inner_count; s32 outer_count;
    s32 inner_delta; s32 outer_delta; Quad quad;
} Scratch;
typedef struct ScratchPrefix {
    u8 pad00[4]; u16 tile; u8 pad06[0x12]; Vec8 *planes; s16 x; s16 y;
    u8 pad22[4]; s32 value; s32 best; s32 limit; u8 pad30[0x1C];
    s16 base_x; s16 base_y; s16 orig_x; s16 orig_y;
    s32 step_x; s32 step_y; s32 inner_count; s32 outer_count;
} ScratchPrefix;
typedef union ScratchArena { Scratch full; ScratchPrefix prefix; } ScratchArena;

s32 func_8008CE08(Scratch *arg0);
extern GlobalState D_80083160;
extern s32 D_800FE480;
extern s32 D_800FE484;

s32 func_8008D5C4(s32 arg0, s32 arg1, s16 arg2) {
    u32 x_sum;
    u16 x_carrier = arg0;
    s16 scan_y = arg1;
    ScratchArena *arena = (ScratchArena *)0x1F800000;
    Scratch *scratch = &arena->full;
    GlobalState *global = &D_80083160;
    MapInfo *map;
    u16 *grid;
    Vec8 *vertices;
    Vec8 *plane_base;
    u32 plane_index;
    u32 selected_index;
    u32 vertex_index;
    s32 a;
    s32 b;
    s32 tile;
    s32 tile2;
    s16 row_y;
    s16 col_x;
    s16 edge;
    s16 origin_x;
    s32 value;
    s32 dx = arg0 & 0x3F;
    s32 dy = arg1 & 0x3F;

    scratch->best = -0x7FFF;
    map = &global->map;
    scratch->x = dx;
    scratch->y = dy;
    scratch->limit = arg2 + 0x14;
    scratch->base_y = dy;
    scratch->planes = map->planes;
    scratch->base_x = dx;
    grid = global->map.grid;
    vertices = map->vertices;
    {
        s32 step_x = scratch->x;
        if (step_x >= 0x20) { dx = 0; step_x = 0x40; }
        else step_x = -0x40;
        *(volatile s32 *)&scratch->step_x = step_x;
    }
    {
        s32 step_y = *(volatile s16 *)&scratch->y < 0x20;
        if (step_y == 0) step_y = 0x40;
        else step_y = -0x40;
        *(volatile s32 *)&scratch->step_y = step_y;
    }
    *(volatile s32 *)&scratch->outer_count = 0;
    scratch->orig_x = x_carrier;
    scratch->orig_y = scan_y;
    scratch->outer_delta = 0;

    while (scratch->outer_count < 2) {
        scan_y = (u16)scratch->orig_y + (u16)scratch->outer_delta;
        row_y = scan_y;
        if (scratch->step_y < 0) goto negative_y;
        if (row_y >= D_800FE484) goto done;
        goto scan_row;
negative_y:
        if (row_y < 0) goto done;
scan_row:
        scratch->inner_count = 0;
        scratch->inner_delta = 0;
        scratch->y = (u16)scratch->base_y - (u16)scratch->outer_delta;
        while (scratch->inner_count < 2) {
            s32 step;
            x_sum = (u16)scratch->orig_x + (u16)scratch->inner_delta;
            step = scratch->step_x;
            x_carrier = x_sum;
            col_x = x_sum;
            if (step < 0) goto negative_x;
            if (col_x >= D_800FE480) break;
            goto scan_cell;
negative_x:
            col_x = x_sum;
            if (col_x < 0) break;
scan_cell:
            a = (s16)x_carrier;
            if (a < 0) a += 0x3F;
            tile = map->x_mask & (a >> 6);
            scratch->tile = tile;
            b = scan_y;
            if (b < 0) b += 0x3F;
            tile2 = tile + ((s16)(map->y_mask & (b >> 6)) << map->shift);
            scratch->tile = tile2;

            if (grid[(s16)scratch->tile] != 0) {
                CellRecord *cell;
                u16 grid_value;
                scratch->x = (u16)scratch->base_x - (u16)scratch->inner_delta;
                grid_value = grid[(s16)scratch->tile];
                cell = map->records[grid_value & 0x3FFF];
                if (!(cell->flags & 0x40)) {
                    cell = (CellRecord *)((u8 *)cell - 0x0C);
                    do {
                    if ((scratch->planes[cell->v8].z > 0) && !(cell->edge_flags & 1)) {
                        scratch->quad.words[0] = vertices[cell->v4].xy;
                        scratch->quad.vals[0] -= scratch->x;
                        scratch->quad.vals[1] -= scratch->y;
                        scratch->quad.words[1] = vertices[cell->v6].xy;
                        scratch->quad.vals[2] -= scratch->x;
                        scratch->quad.vals[3] -= scratch->y;
                        scratch->quad.words[2] = vertices[cell->v2].xy;
                        scratch->quad.vals[4] -= scratch->x;
                        scratch->quad.vals[5] -= scratch->y;
                        scratch->quad.words[3] = vertices[cell->v0].xy;
                        scratch->quad.vals[6] -= scratch->x;
                        scratch->quad.vals[7] -= scratch->y;
                        value = func_8008CE08(scratch);
                        if (value != 0) {
                            s32 term_x;
                            s32 term_y;
                            s32 term_z;
                            if ((value & 1) != 0)
                                plane_index = cell->v8;
                            else
                                plane_index = cell->v8 + ((value & 1) != 0);
                            plane_base = scratch->planes;
                            vertex_index = cell->v0;
                            origin_x = scratch->x;
                            if (plane_base != 0)
                                selected_index = plane_index;
                            else
                                selected_index = plane_index + (plane_base != 0);
                            edge = plane_base[selected_index].z;
                            term_x = (s16)plane_base[selected_index].xy *
                                     ((s16)vertices[vertex_index].xy - origin_x);
                            term_y = (s16)(plane_base[selected_index].xy >> 16) *
                                     ((s16)(vertices[vertex_index].xy >> 16) -
                                      (s16)scratch->y);
                            term_z = edge * vertices[vertex_index].z;
                            value = term_x + term_y + term_z;
                            scratch->value = value / edge;
                            if (scratch->limit >= scratch->value &&
                                scratch->best < scratch->value)
                                scratch->best = scratch->value;
                        }
                    }
                    if ((s8)cell->edge_flags < 0) break;
                    cell = (CellRecord *)((u8 *)cell - 0x0C);
                    } while (1);
                }
            }
            scratch->inner_count += 1;
            scratch->inner_delta += scratch->step_x;
        }
        scratch->outer_count += 1;
        scratch->outer_delta += scratch->step_y;
    }
done:
    return (s16)(u16)scratch->best;
}
