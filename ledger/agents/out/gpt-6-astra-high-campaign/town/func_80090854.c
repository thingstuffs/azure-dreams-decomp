#include "common.h"

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

extern Global_80090854 D_80083160;
extern s32 D_800FE480;
extern s32 D_800FE484;

extern s32 func_8008CE08(Scratch_80090854 *);

/* Finds the greatest cell-plane intersection within the query position's search limit. */
s32 func_8008DFB4(s16 query_x, u16 query_y, u16 query_z)
{
    Scratch_80090854 *scratch = (Scratch_80090854 *)0x1F800000;
    s16 scan_z;
    s16 scan_x;
    s32 block = (s16)(query_x & -0x40);
    Global_80090854 *global = &D_80083160;
    register Map_80090854 *map ASM_REG("$20");
    register u16 *tiles ASM_REG("$21");
    register Vec_80090854 *vertices ASM_REG("$19");

    scan_x = query_x;
    scan_z = query_y;
    map = &global->map;

    scratch->limit = ((s16)query_x - block) + 0x14;
    scratch->best = 0;
    scratch->block = block;
    query_y &= 0x3F;
    scratch->x = query_y;
    scratch->z = query_z;
    scratch->planes = map->planes;
    query_x &= 0x3F;
    scratch->result = query_x;
    scratch->origin_x = query_y;
    tiles = global->map.tiles;
    vertices = map->vertices;

    if (query_x >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }

    if ((s16)scratch->x >= 0x20) {
        s32 positive_step;

        positive_step = 0x40;
        scratch->z_step = positive_step;
    } else {
        register s32 negative_step;

        negative_step = -0x40;
        scratch->z_step = negative_step;
    }

    scratch->outer_count = 0;
    scratch->scan_x = scan_x;
    scratch->scan_z = scan_z;
    scratch->outer_offset = 0;
    if (scratch->outer_count >= 2) {
        goto finished;
    }

outer_loop:
    {
        s16 next_z = (u16)scratch->scan_z + (u16)scratch->outer_offset;

        scan_z = next_z;
        if (scratch->z_step >= 0) {
            if (next_z >= D_800FE484) {
                goto finished;
            }
        } else if (next_z < 0) {
            goto finished;
        }
    }

    scratch->inner_count = 0;
    scratch->inner_offset = 0;
    scratch->x = (u16)scratch->origin_x - (u16)scratch->outer_offset;
    if (scratch->inner_count >= 2) {
        goto next_outer;
    }

inner_loop:
    {
        s16 next_x = (u16)scratch->scan_x + (u16)scratch->inner_offset;

        scan_x = next_x;
        if (scratch->x_step >= 0) {
            if (next_x >= D_800FE480) {
                goto next_outer;
            }
        } else if (next_x < 0) {
            goto next_outer;
        }
    }

    {
        s16 tile_x;
        u16 tile_index;
        s32 signed_x;
        s32 shifted_x;

        shifted_x = (s32)((u32)(u16)scan_x << 16);
        signed_x = shifted_x >> 16;
        tile_x = map->x_mask & (signed_x / 64);
        scratch->tile = tile_x;
        tile_index = tile_x +
            ((s16)(map->z_mask & (scan_z / 64)) << map->shift);
        scratch->tile = tile_index;

        if (tiles[scratch->tile] != 0) {
            Cell_80090854 *cell;
            u8 *cell_flags;
            u16 tile_value;
            s32 vertex_delta;

            scratch->inner_bias = scratch->inner_offset;
            tile_value = tiles[scratch->tile];
            cell = map->cells[tile_value & 0x3FFF];
            cell_flags = (u8 *)cell + 0x16;

            for (;;) {
                if (scratch->planes[*(u16 *)(cell_flags - 6)].x > 0 &&
                    !(cell_flags[1] & 1)) {
                    s32 plane_x;

                    vertex_delta = (u16)vertices[*(u16 *)(cell_flags - 0x12)].y;
                    vertex_delta -= (u16)scratch->x;
                    scratch->quad[0] = vertex_delta;
                    vertex_delta = (u16)vertices[*(u16 *)(cell_flags - 0x12)].z;
                    vertex_delta -= (u16)scratch->z;
                    scratch->quad[1] = vertex_delta;
                    vertex_delta = (u16)vertices[*(u16 *)(cell_flags - 0x10)].y;
                    vertex_delta -= (u16)scratch->x;
                    scratch->quad[2] = vertex_delta;
                    vertex_delta = (u16)vertices[*(u16 *)(cell_flags - 0x10)].z;
                    vertex_delta -= (u16)scratch->z;
                    scratch->quad[3] = vertex_delta;
                    vertex_delta = (u16)vertices[*(u16 *)(cell_flags - 0x14)].y;
                    vertex_delta -= (u16)scratch->x;
                    scratch->quad[4] = vertex_delta;
                    vertex_delta = (u16)vertices[*(u16 *)(cell_flags - 0x14)].z;
                    vertex_delta -= (u16)scratch->z;
                    scratch->quad[5] = vertex_delta;
                    vertex_delta = (u16)vertices[cell->v0].y;
                    vertex_delta -= (u16)scratch->x;
                    scratch->quad[6] = vertex_delta;
                    vertex_delta = (u16)vertices[cell->v0].z;
                    vertex_delta -= (u16)scratch->z;
                    scratch->quad[7] = vertex_delta;

                    if (func_8008CE08(scratch) != 0) {
                        u16 plane_index = *(u16 *)(cell_flags - 6);
                        u16 vertex_index = cell->v0;
                        register Vec_80090854 *plane;
                        register Vec_80090854 *vertex;
                        s32 delta_y;
                        s32 delta_z;
                        s32 y_product;
                        s32 z_product;
                        s32 x_product;

                        plane = (Vec_80090854 *)(plane_index * 8 + (u32)scratch->planes);
                        vertex = (Vec_80090854 *)(vertex_index * 8 + (u32)vertices);
                        delta_y = vertex->y - (s16)scratch->x;
                        delta_z = vertex->z - (s16)scratch->z;
                        y_product = plane->y * delta_y;
                        z_product = plane->z * delta_z;
                        x_product = plane->x * vertex->x;
                        plane_x = (y_product + z_product + x_product) / plane->x;
                        scratch->result = plane_x;
                        scratch->result += scratch->inner_bias;
                        if (scratch->limit >= scratch->result &&
                            scratch->best < scratch->result) {
                            scratch->best = scratch->result;
                        }
                    }
                }

                {
                    register u16 end_flags ASM_REG("$3");
                    end_flags = *(u16 *)cell_flags & 0x80FF;
                    if (end_flags != 0x8001) {
                        cell_flags += 0x18;
                        ASM_KEEP(cell_flags);
                        cell = (Cell_80090854 *)((u8 *)cell + 0x18);
                    } else {
                        break;
                    }
                }
            }
        }
    }

    scratch->inner_count++;
    scratch->inner_offset += scratch->x_step;
    if (scratch->inner_count < 2) {
        goto inner_loop;
    }

next_outer:
    scratch->outer_count++;
    scratch->outer_offset += scratch->z_step;
    if (scratch->outer_count < 2) {
        goto outer_loop;
    }

finished:
    if (scratch->best == 0) {
        return 0;
    }
    {
        s32 result;
        result = (s16)((u16)scratch->block + (u16)scratch->best);
        return result;
    }
}
