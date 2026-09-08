#include "common.h"

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

extern Global_8008EA20 D_80083160;
extern s32 D_800FE480;
extern s32 D_800FE484;

extern s32 func_8008CE08(Scratch_8008EA20 *scratch);

/* Returns the highest valid cell height within the scan limit, or zero if none. */
s32 func_8008EA20(s32 world_x, s32 world_z, s32 world_y)
{
    Scratch_8008EA20 *scratch = (Scratch_8008EA20 *)0x1F800000;
    s16 scan_x = world_x;
    s16 scan_z = world_z;
    s16 query_y = world_y;
    s32 z_base;
    s32 tile_mask;
    Global_8008EA20 *global = &D_80083160;
    Map_8008EA20 *map = &global->map;
    u16 *tiles;
    Vec_8008EA20 *vertices;

    tile_mask = -0x40;
    z_base = (s32)((u32)(world_z & tile_mask) << 16) >> 16;
    scratch->limit = ((s16)world_z - z_base) + 0x14;
    scratch->best = 0;
    scratch->z_base = z_base;
    scratch->x = world_x & 0x3F;
    scratch->y = query_y;
    scratch->heights = map->heights;
    scratch->z = world_z & 0x3F;
    scratch->x_origin = world_x & 0x3F;
    tiles = global->map.tiles;
    vertices = map->vertices;

    if ((world_x & 0x3F) >= 0x20) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = tile_mask;
    }

    if (scratch->z < 0x20) {
        scratch->z_step = -0x40;
    } else {
        scratch->z_step = 0x40;
    }

    scratch->z_count = 0;
    scratch->x_start = scan_x;
    scratch->z_start = scan_z;
    scratch->z_offset_acc = 0;

    while (scratch->z_count < 2) {
        scan_z = (u16)scratch->z_start + (u16)scratch->z_offset_acc;
        if (scratch->z_step >= 0) {
            if (scan_z >= D_800FE484) {
                break;
            }
        } else if (scan_z < 0) {
            break;
        }

        scratch->x_count = 0;
        scratch->x_offset = 0;
        scratch->z_offset = (u16)scratch->z_offset_acc;

        while (scratch->x_count < 2) {
            s32 grid_x;
            s32 grid_z;

            scan_x = (u16)scratch->x_start + (u16)scratch->x_offset;
            if (scratch->x_step >= 0) {
                if (scan_x >= D_800FE480) {
                    break;
                }
            } else if (scan_x < 0) {
                break;
            }

            grid_x = scan_x;
            if (grid_x < 0) {
                grid_x += 0x3F;
            }
            scratch->tile = map->x_mask & (grid_x >> 6);

            grid_z = scan_z;
            if (grid_z < 0) {
                grid_z += 0x3F;
            }
            scratch->tile +=
                (s16)(map->z_mask & (grid_z >> 6)) << map->shift;

            if (tiles[(s16)scratch->tile] != 0) {
                u16 tile_entry;
                Cell_8008EA20 *cell;

                scratch->x =
                    (u16)scratch->x_origin - (u16)scratch->x_offset;
                tile_entry = tiles[(s16)scratch->tile];
                cell = map->cells[tile_entry & 0x3FFF];

                for (;;) {
                    if (scratch->heights[cell->height_index].y > 0 &&
                        !(((u8 *)&cell->flags)[1] & 1)) {
                        s32 cell_height;

                        scratch->quad[0] =
                            vertices[cell->v0].x - (u16)scratch->x;
                        scratch->quad[1] =
                            vertices[cell->v0].z - (u16)scratch->y;
                        scratch->quad[2] =
                            vertices[cell->v1].x - (u16)scratch->x;
                        scratch->quad[3] =
                            vertices[cell->v1].z - (u16)scratch->y;
                        scratch->quad[4] =
                            vertices[cell->v2].x - (u16)scratch->x;
                        scratch->quad[5] =
                            vertices[cell->v2].z - (u16)scratch->y;
                        scratch->quad[6] =
                            vertices[cell->v3].x - (u16)scratch->x;
                        scratch->quad[7] =
                            vertices[cell->v3].z - (u16)scratch->y;

                        if (func_8008CE08(scratch) != 0) {
                            s16 local_x = scratch->x;

                            cell_height =
                                (scratch->heights[cell->height_index].x *
                                     (vertices[cell->v0].x - local_x) +
                                 scratch->heights[cell->height_index].z *
                                     (vertices[cell->v0].z - (s16)scratch->y) +
                                 scratch->heights[cell->height_index].y *
                                     vertices[cell->v0].y) /
                                scratch->heights[cell->height_index].y;
                            scratch->z = cell_height;
                            scratch->z += (u16)scratch->z_offset;
                            if (scratch->limit >= scratch->z &&
                                scratch->best < scratch->z) {
                                scratch->best = scratch->z;
                            }
                        }
                    }

                    if ((cell->flags & 0x80FF) == 0x8001) {
                        break;
                    }
                    cell = (Cell_8008EA20 *)((u8 *)cell + 0x18);
                }
            }

            scratch->x_count++;
            scratch->x_offset += scratch->x_step;
        }

        scratch->z_count++;
        scratch->z_offset_acc += scratch->z_step;
    }

    if (scratch->best == 0) {
        return 0;
    }
    return (s16)((u16)scratch->z_base + (u16)scratch->best);
}
