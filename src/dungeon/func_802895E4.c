#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} Pos;

typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} DungeonCell;

typedef struct {
    u16 unk0;
    u16 tile;
} Walker;

extern DungeonCell D_800EA000[];

extern s32 func_800A6D30(void);
extern u32 func_800A07D0(s16 x0, s16 y0, s16 x1, s16 y1);

/* Carve a corridor from start toward dest in up to three straight legs: stamp the walker's tile id into every cell it crosses, add the per-step cost, give up with -1 when a cell already holds an incompatible tile, and return the step count. */
s16 func_8001C5E4(Pos *start, Pos *dest, s16 rnd, s16 *out_x, s16 *out_y,
                  Walker *walker, s32 *cost) {
    s16 count;
    s16 cx;
    s16 cy;
    s16 dir;
    s16 dst_x;
    s16 dst_y;
    s16 dir_slot;
    s16 range_x;
    s16 range_y;
    s16 wx;
    s16 wy;
    s32 delta;
    s32 delta2;
    s32 idy;
    GameWork *gw;
    MapGrid *st;
    u32 r;

    count = 0;
    cy = start->y;
    cx = start->x;
    delta = dest->x;
    delta = delta - cx;
    dir = start->dir;
    delta = abs(delta);
    range_x = delta - 4;
    gw = &gameWork;
    dir_slot = dir;
    dst_y = dest->y;
    dst_x = dest->x;
    if (range_x <= 0) {
        range_x = 1;
    }
    st = &gw->map;
    wx = range_x;
    if (wx >= 5) {
        wx = 4;
    }
    range_x = range_x - wx;
    if (range_x <= 0) {
        range_x = 1;
    }

    idy = (u32)(u16)dst_y << 16;
    idy >>= 16;
    delta = (u32)(u16)cy << 16;
    delta >>= 16;
    delta2 = abs(idy - delta);
    range_y = delta2 - 4;
    if (range_y <= 0) {
        range_y = 1;
    }
    wy = range_y;
    if (wy >= 5) {
        wy = 4;
    }
    range_y = range_y - wy;
    if (range_y <= 0) {
        range_y = 1;
    }

    if (rnd != 0) {
        s16 r;

        r = (u16)func_800A6D30() % range_x;
        *out_x = r;
        wx = cx + r * dirStepX[dir] + dirStepX[dir] * wx;
        r = (u16)func_800A6D30() % range_y;
        *out_y = r;
        wy = cy + r * dirStepY[dir] + dirStepY[dir] * wy;
    } else {
        wx = cx + *out_x * dirStepX[dir] + dirStepX[dir] * wx;
        wy = cy + *out_y * dirStepY[dir] + dirStepY[dir] * wy;
    }

    for (;;) {
        s32 iy;
        s32 ix;
        s32 tile;
        DungeonCell *cell;
        s32 d;

        tile = walker->tile & 0xFFE0;
        iy = cy;
        cell = &D_800EA000[(iy << st->shiftX) + (ix = cx)];
        if (cell->value != 16384) {
            d = abs(cell->value - (s16)tile);
            if (d >= 33) {
                return -1;
            }
        }
        cell->value = tile;
        if (ix == wx && iy == wy) {
            break;
        }
        *(s32 *)walker += *cost;
        count++;
        cx += dirStepX[dir];
        cy += dirStepY[dir];
    }

    if (wx != dst_x || wy != dst_y) {
        if (dirStepX[dir_slot] != 0) {
            wy = dst_y;
        } else {
            wx = dst_x;
        }
        r = func_800A07D0(cx, cy, wx, wy);
        dir = (r >> 9) & 6;
        for (;;) {
            s32 iy;
            s32 ix;
            s32 tile;
            DungeonCell *cell;
            s32 d;

            tile = walker->tile & 0xFFE0;
            iy = cy;
            cell = &D_800EA000[(iy << st->shiftX) + (ix = cx)];
            if (cell->value != 16384) {
                d = abs(cell->value - (s16)tile);
                if (d >= 33) {
                    return -1;
                }
            }
            cell->value = tile;
            if (ix == wx && iy == wy) {
                break;
            }
            *(s32 *)walker += *cost;
            count++;
            cx += dirStepX[dir];
            cy += dirStepY[dir];
        }
    }

    if (wx != dst_x || wy != dst_y) {
        r = func_800A07D0(cx, cy, dst_x, dst_y);
        dir = (r >> 9) & 6;
        for (;;) {
            s32 iy;
            s32 ix;
            s32 tile;
            DungeonCell *cell;
            s32 d;

            tile = walker->tile & 0xFFE0;
            iy = cy;
            cell = &D_800EA000[(iy << st->shiftX) + (ix = cx)];
            if (cell->value != 16384) {
                d = abs(cell->value - (s16)tile);
                if (d >= 33) {
                    return -1;
                }
            }
            cell->value = tile;
            if (ix == dst_x && iy == dst_y) {
                break;
            }
            *(s32 *)walker += *cost;
            count++;
            cx += dirStepX[dir];
            cy += dirStepY[dir];
        }
    }
    return count;
}
