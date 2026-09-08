#include "common.h"

typedef struct Vec8 {
    u32 xy;
    s16 z;
    s16 pad;
} Vec8;

typedef union Quad {
    u32 words[4];
    u16 halves[8];
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

extern TargetGlobal D_80083160;
extern u8 D_800CFCAC[];
extern s32 D_800FE480;
extern s32 D_800FE484;

extern s32 func_8008CE08();

/* Finds the lowest qualifying surface height and plane at the query position. */
s32 func_8008D0B8(u32 query_x, u32 query_y, s16 query_height, void **plane_out)
{
    TargetScratch *scratch;
    TargetGlobal *globals;
    TargetMap *world;
    u16 *tiles;
    Vec8 *vertices;
    Vec8 *planes;
    u8 *face;
    u16 x;
    s16 y;
    void **result_plane;
    s32 threshold;
    s32 left_half;
    s32 cell_x_coord;
    s32 cell_y_coord;
    u16 cell;
    u16 local_x;
    u16 local_y;
    s32 height;
    s32 x_step;
    s32 x_sum;
    s32 signed_x;
    u32 scan_x_value;
    u32 query_x_value;
    u32 masked_y;
    u8 flags;

    query_x_value = query_x + query_y;
    query_x_value -= query_y;
    x = query_x_value;
    y = query_y;
    result_plane = plane_out;
    scratch = (TargetScratch *)0x1F800000;
    scratch->best = 0x400;
    scratch->result = (void *)D_800CFCAC;
    masked_y = query_y & 0x3F;
    globals = &D_80083160;
    world = &globals->map;
    {
        u32 masked_x;
        masked_x = query_x & 0x3F;
        threshold = query_height - 0x14;
        scratch->origin_x = masked_x;
        scratch->origin_y = masked_y;
        do { } while (0);
        planes = world->planes;
        scratch->x_base = masked_x;
        left_half = (s32)masked_x < 0x20;
        scratch->threshold = threshold;
        scratch->y_base = masked_y;
        scratch->planes = planes;
        tiles = world->tiles;
        vertices = world->vertices;
    }

    if (!left_half) {
        scratch->x_step = 0x40;
    } else {
        scratch->x_step = -0x40;
    }
    if ((s16)scratch->origin_y < 0x20) {
        scratch->y_step = -0x40;
    } else {
        scratch->y_step = 0x40;
    }

    scratch->outer_count = 0;
    scratch->x_scan = x;
    scratch->y_scan = y;
    scratch->outer_offset = 0;

    while (scratch->outer_count < 2) {
        y = scratch->y_scan + scratch->outer_offset;
        if (scratch->y_step >= 0) {
            if (y < D_800FE484) {
                goto y_valid;
            }
            goto done;
        }
        if (y < 0) {
            goto done;
        }

    y_valid:
        scratch->inner_count = 0;
        scratch->inner_offset = 0;
        scratch->origin_y = scratch->y_base - scratch->outer_offset;

        while (scratch->inner_count < 2) {
            x_sum = scratch->x_scan + (u16)scratch->inner_offset;
            if ((u16)x_sum != 0) {
                x_step = scratch->x_step;
            } else {
                x_step = scratch->x_step + ((u16)x_sum != 0);
            }
            scan_x_value = (u32)x_sum + (u32)x_step;
            scan_x_value -= (u32)x_step;
            x = scan_x_value;
            if (x_step >= 0) {
                if ((s16)x_sum >= D_800FE480) {
                    goto next_outer;
                }
                goto x_valid;
            }
            signed_x = (s16)x_sum;
            if ((s16)signed_x < 0) {
                goto next_outer;
            }

        x_valid:
            cell_x_coord = (s16)x;
            if (cell_x_coord < 0) {
                cell_x_coord += 0x3F;
            }
            cell = world->x_mask & (cell_x_coord >> 6);
            scratch->cell = cell;
            cell_y_coord = (s16)y;
            if (cell_y_coord < 0) {
                cell_y_coord += 0x3F;
            }
            cell += (s16)(world->y_mask & (cell_y_coord >> 6)) << world->shift;
            scratch->cell = cell;
            if (tiles[(s16)cell] == 0) {
                goto next_inner;
            }

            scratch->origin_x = scratch->x_base - scratch->inner_offset;
            face = world->cells[(tiles[(s16)scratch->cell] & 0x3FFF)];
            while (scratch->planes[*(u16 *)(face + 0x10)].z < 0) {
                if (!(face[0x17] & 1)) {
                    local_x = scratch->origin_x;
                    local_y = scratch->origin_y;

                    scratch->quad.words[0] = vertices[*(u16 *)(face + 0)].xy;
                    scratch->quad.halves[0] -= local_x;
                    scratch->quad.halves[1] -= local_y;

                    scratch->quad.words[1] = vertices[*(u16 *)(face + 2)].xy;
                    scratch->quad.halves[2] -= local_x;
                    scratch->quad.halves[3] -= local_y;

                    scratch->quad.words[2] = vertices[*(u16 *)(face + 6)].xy;
                    scratch->quad.halves[4] -= local_x;
                    scratch->quad.halves[5] -= local_y;

                    scratch->quad.words[3] = vertices[*(u16 *)(face + 4)].xy;
                    scratch->quad.halves[6] -= local_x;
                    scratch->quad.halves[7] -= local_y;
                    if (func_8008CE08(scratch) != 0) {
                        height = ((s16)scratch->planes[*(u16 *)(face + 0x10)].xy *
                                      ((s16)vertices[*(u16 *)face].xy -
                                       (s16)scratch->origin_x) +
                                  (s16)(scratch->planes[*(u16 *)(face + 0x10)].xy >> 16) *
                                      ((s16)(vertices[*(u16 *)face].xy >> 16) -
                                       (s16)scratch->origin_y) +
                                  scratch->planes[*(u16 *)(face + 0x10)].z *
                                      vertices[*(u16 *)face].z) /
                                 scratch->planes[*(u16 *)(face + 0x10)].z;
                        scratch->height = height;
                        if (height >= scratch->threshold && height < scratch->best) {
                            scratch->best = height;
                            scratch->result = &scratch->planes[*(u16 *)(face + 0x10)];
                        }
                    }
                }

                flags = face[0x16];
                if ((flags & 0xF) == 1) {
                    if ((s8)face[0x17] < 0) {
                        goto next_inner;
                    }
                    if (flags & 0xF0) {
                        face += ((flags >> 4) * 3 << 3) + 0x18;
                        continue;
                    }
                }
                face += 0x18;
            }
        next_inner:
            scratch->inner_count++;
            scratch->inner_offset += scratch->x_step;
        }

    next_outer:
        scratch->outer_count++;
        scratch->outer_offset += scratch->y_step;
    }

done:
    *result_plane = scratch->result;
    return (s16)scratch->best;
}
