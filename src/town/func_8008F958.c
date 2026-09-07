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

s32 func_8008D0B8(u32 arg0, u32 arg1, s16 arg2, void **arg3)
{
    TargetScratch *sc;
    TargetGlobal *base;
    TargetMap *world;
    u16 *lookup;
    Vec8 *vertices;
    Vec8 *planes;
    u8 *node;
    u16 x;
    s16 y;
    void **out;
    s32 threshold;
    s32 side;
    s32 a;
    s32 b;
    u16 cell;
    u16 ox;
    u16 oy;
    s32 height;
    s32 x_step;
    s32 x_sum;
    s32 x_check;
    u32 x_math;
    u32 x_entry;
    u32 masked_y;
    u8 flags;

    x_entry = arg0 + arg1;
    x_entry -= arg1;
    x = x_entry;
    y = arg1;
    out = arg3;
    sc = (TargetScratch *)0x1F800000;
    sc->best = 0x400;
    sc->result = (void *)D_800CFCAC;
    masked_y = arg1 & 0x3F;
    base = &D_80083160;
    world = &base->map;
    {
    u32 masked_x;
    masked_x = arg0 & 0x3F;
    threshold = arg2 - 0x14;
    sc->origin_x = masked_x;
    sc->origin_y = masked_y;
    do { } while (0);
    planes = world->planes;
    sc->x_base = masked_x;
    side = (s32)masked_x < 0x20;
    sc->threshold = threshold;
    sc->y_base = masked_y;
    sc->planes = planes;
    lookup = world->tiles;
    vertices = world->vertices;
    }

    if (!side) {
        sc->x_step = 0x40;
    } else {
        sc->x_step = -0x40;
    }
    if ((s16)sc->origin_y < 0x20) {
        sc->y_step = -0x40;
    } else {
        sc->y_step = 0x40;
    }

    sc->outer_count = 0;
    sc->x_scan = x;
    sc->y_scan = y;
    sc->outer_offset = 0;

    while (sc->outer_count < 2) {
    y = sc->y_scan + sc->outer_offset;
    if (sc->y_step >= 0) {
        if (y < D_800FE484) {
            goto y_valid;
        }
        goto done;
    }
    if (y < 0) {
        goto done;
    }

y_valid:
    sc->inner_count = 0;
    sc->inner_offset = 0;
    sc->origin_y = sc->y_base - sc->outer_offset;

    while (sc->inner_count < 2) {
    x_sum = sc->x_scan + (u16)sc->inner_offset;
    if ((u16)x_sum != 0) {
        x_step = sc->x_step;
    } else {
        x_step = sc->x_step + ((u16)x_sum != 0);
    }
    x_math = (u32)x_sum + (u32)x_step;
    x_math -= (u32)x_step;
    x = x_math;
    if (x_step >= 0) {
        if ((s16)x_sum >= D_800FE480) {
            goto next_outer;
        }
        goto x_valid;
    }
    x_check = (s16)x_sum;
    if ((s16)x_check < 0) {
        goto next_outer;
    }

x_valid:
    a = (s16)x;
    if (a < 0) {
        a += 0x3F;
    }
    cell = world->x_mask & (a >> 6);
    sc->cell = cell;
    b = (s16)y;
    if (b < 0) {
        b += 0x3F;
    }
    cell += (s16)(world->y_mask & (b >> 6)) << world->shift;
    sc->cell = cell;
    if (lookup[(s16)cell] == 0) {
        goto next_inner;
    }

    sc->origin_x = sc->x_base - sc->inner_offset;
    node = world->cells[(lookup[(s16)sc->cell] & 0x3FFF)];
    while (sc->planes[*(u16 *)(node + 0x10)].z < 0) {
    if (!(node[0x17] & 1)) {
        ox = sc->origin_x;
        oy = sc->origin_y;

        sc->quad.words[0] = vertices[*(u16 *)(node + 0)].xy;
        sc->quad.halves[0] -= ox;
        sc->quad.halves[1] -= oy;

        sc->quad.words[1] = vertices[*(u16 *)(node + 2)].xy;
        sc->quad.halves[2] -= ox;
        sc->quad.halves[3] -= oy;

        sc->quad.words[2] = vertices[*(u16 *)(node + 6)].xy;
        sc->quad.halves[4] -= ox;
        sc->quad.halves[5] -= oy;

        sc->quad.words[3] = vertices[*(u16 *)(node + 4)].xy;
        sc->quad.halves[6] -= ox;
        sc->quad.halves[7] -= oy;
        if (func_8008CE08(sc) != 0) {
            height = ((s16)sc->planes[*(u16 *)(node + 0x10)].xy *
                          ((s16)vertices[*(u16 *)node].xy -
                           (s16)sc->origin_x) +
                      (s16)(sc->planes[*(u16 *)(node + 0x10)].xy >> 16) *
                          ((s16)(vertices[*(u16 *)node].xy >> 16) -
                           (s16)sc->origin_y) +
                      sc->planes[*(u16 *)(node + 0x10)].z *
                          vertices[*(u16 *)node].z) /
                     sc->planes[*(u16 *)(node + 0x10)].z;
            sc->height = height;
            if (height >= sc->threshold && height < sc->best) {
                sc->best = height;
                sc->result = &sc->planes[*(u16 *)(node + 0x10)];
            }
        }
    }

    flags = node[0x16];
    if ((flags & 0xF) == 1) {
        if ((s8)node[0x17] < 0) {
            goto next_inner;
        }
        if (flags & 0xF0) {
            node += ((flags >> 4) * 3 << 3) + 0x18;
            continue;
        }
    }
    node += 0x18;
    }
next_inner:
    sc->inner_count++;
    sc->inner_offset += sc->x_step;
    }

next_outer:
    sc->outer_count++;
    sc->outer_offset += sc->y_step;
    }

done:
    *out = sc->result;
    return (s16)sc->best;
}
