#include "common.h"

typedef struct {
    s32 *part0;
    s32 *part1;
} Parts92360;

typedef struct {
    u8 pad0[8];
    Parts92360 parts;
} Object92360;

typedef struct {
    s32 axis;
    s32 amount;
} Result92360;

extern Result92360 D_800CFE60[];

Result92360 *func_8008FAC0(Object92360 *arg0, Object92360 *arg1)
{
    register s32 *a0_part1 = arg0->parts.part1;
    register s32 *a1_part1 = arg1->parts.part1;
    register s32 *a0_part0 = arg0->parts.part0;
    register s32 *a1_part0 = arg1->parts.part0;
    s32 *a0_values1 = a0_part1;
    s32 *a0_values = a0_part0;
    s32 *a1_values = a1_part0;
    s32 *a1_extent = a1_part1;
    register s32 lx, rx, ly, ry, lz, rz;
    register s32 dx, dx2, dy, dy2, dz, dz2, tmp;
    register s32 ax, ax2, ay, ay2, az, az2;
    register s32 fx, fy, fz1, fz2, c1, c2, c3;

    lx = a0_values[0] + a0_values1[0];
    rx = a1_values[0] + a1_part1[0];
    dx = lx - (rx + a1_extent[3]);
    if (dx > 0) return 0;
    tmp = lx + a0_part1[3];
    dx2 = tmp - rx;
    c2 = 0;
    if (dx2 < 0) goto ret0;

    ly = a0_values[1] + a0_values1[1];
    ry = a1_values[1] + a1_part1[1];
    dy = ly - (ry + a1_extent[4]);
    if (dy > 0) return 0;
    dy2 = (ly + a0_part1[4]) - ry;
    c2 = 0;
    if (dy2 < 0) goto ret0;

    lz = a0_values[2] + a0_values1[2];
    rz = a1_values[2] + a1_part1[2];
    dz = lz - (rz + a1_extent[5]);
    if (dz > 0) return 0;
    dz2 = (lz + a0_part1[5]) - rz;
    if (dz2 < 0) return 0;

    do {
        ax = __builtin_abs(dx);
    } while (0);
    ax2 = __builtin_abs(dx2);
    if (ax2 < ax) dx = dx2;
    ay = __builtin_abs(dy);
    ay2 = __builtin_abs(dy2);
    if (ay2 < ay) dy = dy2;
    az = __builtin_abs(dz);
    az2 = __builtin_abs(dz2);
    if (az2 < az) dz = dz2;

    if (dx == 0) {
        if (dy == 0) return 0;
        if (dz == 0) return 0;
    }
    if (dy != 0) goto choose;
    if (dz != 0) goto choose;
ret0:
    return 0;

choose:
    fx = __builtin_abs(dx);
    fy = __builtin_abs(dy);
    if (fx < fy) {
        fz1 = __builtin_abs(dz);
        c1 = fy < fz1;
        if (c1) goto use_x;
        c2 = fx < fz1;
        if (!c2) goto use_z;
use_x:
        D_800CFE60[0].axis = 0;
        D_800CFE60[0].amount = dx;
        return D_800CFE60;
    }
    fz2 = __builtin_abs(dz);
    c3 = fy < fz2;
    if (c3) {
        D_800CFE60[0].axis = 1;
        D_800CFE60[0].amount = dy;
        return D_800CFE60;
    }
use_z:
    D_800CFE60[0].axis = 2;
    D_800CFE60[0].amount = dz;
    return D_800CFE60;
}
