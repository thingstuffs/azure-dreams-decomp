#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} Pos;

typedef struct {
    s16 unused[10];
    s16 stride;
} DungeonState;

typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} DungeonCell;

typedef struct {
    u16 unk0;
    u16 tile;
} Walker;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern DungeonCell D_800EA000[];
extern DungeonState D_8008333C;
extern DungeonState D_80083160;

extern s32 func_800A6D30(void);
extern u32 func_800A07D0(s16 x0, s16 y0, s16 x1, s16 y1);

/* Carve a corridor from start toward dest in up to three straight legs: stamp the walker's tile id into every cell it crosses, add the per-step cost, give up with -1 when a cell already holds an incompatible tile, and return the step count. */
s32 func_8001C5E4(Pos *start, Pos *dest, s16 rnd, s16 *out_x, s16 *out_y,
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
    s32 icy;
    DungeonState *dead;
    DungeonState *st;
    u32 r;

    st = &D_8008333C;
    count = 0;
    cy = start->y;
    delta2 = start->x;
    cx = delta2;
    delta = dest->x;
    delta = delta - delta2;
    dir = start->dir;
    ASM_USE2_NV(delta2, cx);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (delta < 0) {
        delta = -delta;
    }
    range_x = delta - 4;
    dead = &D_80083160;
    dir_slot = dir;
    dst_y = dest->y;
    ASM_KEEP(dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(dir);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(dest);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    dst_x = dest->x;
    if (range_x <= 0) {
        range_x = 1;
    }
    wx = range_x;
    if (wx >= 5) {
        wx = 4;
    }
    range_x = range_x - wx;
    if (range_x <= 0) {
        range_x = 1;
    }

    ASM_USE_NV(dst_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    icy = cy;
    delta2 = dst_y - icy;
    if (delta2 < 0) {
        delta2 = -delta2;
    }
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
        wx = cx + r * D_8006CCD8[dir] + D_8006CCD8[dir] * wx;
        r = (u16)func_800A6D30() % range_y;
        *out_y = r;
        wy = cy + r * D_8006CCE8[dir] + D_8006CCE8[dir] * wy;
    } else {
        wx = cx + *out_x * D_8006CCD8[dir] + D_8006CCD8[dir] * wx;
        wy = cy + *out_y * D_8006CCE8[dir] + D_8006CCE8[dir] * wy;
    }

    for (;;) {
        s32 iy;
        s32 ix;
        s32 tile;
        DungeonCell *cell;
        s32 d;

        tile = walker->tile & 0xFFE0;
        iy = cy;
        cell = &D_800EA000[(iy << st->stride) + (ix = cx)];
        if (cell->value != 16384) {
            d = cell->value - (s16)tile;
            if (d < 0) {
                d = -d;
            }
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
        cx += D_8006CCD8[dir];
        cy += D_8006CCE8[dir];
    }

    if (wx != dst_x || wy != dst_y) {
        if (D_8006CCD8[dir_slot] != 0) {
            wy = dst_y;
        } else {
            wx = dst_x;
        }
        r = func_800A07D0(cx, cy, wx, wy);
        for (;;) {
            s32 iy;
            s32 ix;
            s32 tile;
            DungeonCell *cell;
            s32 d;

            tile = walker->tile & 0xFFE0;
            iy = cy;
            cell = &D_800EA000[(iy << st->stride) + (ix = cx)];
            if (cell->value != 16384) {
                d = cell->value - (s16)tile;
                if (d < 0) {
                    d = -d;
                }
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
            cx += D_8006CCD8[(r >> 9) & 6];
            cy += D_8006CCE8[(r >> 9) & 6];
        }
    }

    if (wx != dst_x || wy != dst_y) {
        r = func_800A07D0(cx, cy, dst_x, dst_y);
        for (;;) {
            s32 iy;
            s32 ix;
            s32 tile;
            DungeonCell *cell;
            s32 d;

            tile = walker->tile & 0xFFE0;
            iy = cy;
            cell = &D_800EA000[(iy << st->stride) + (ix = cx)];
            if (cell->value != 16384) {
                d = cell->value - (s16)tile;
                if (d < 0) {
                    d = -d;
                }
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
            cx += D_8006CCD8[(r >> 9) & 6];
            cy += D_8006CCE8[(r >> 9) & 6];
        }
    }
    return count;
}
