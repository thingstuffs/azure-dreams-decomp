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

s32 func_8001C5E4(Pos *start, Pos *dest, s16 rnd, s16 *outX, s16 *outY,
                  Walker *walker, s32 *cost) {
    s16 count;
    s16 cx;
    s16 cy;
    s16 dir;
    s16 dstX;
    s16 dstY;
    s16 dirSlot;
    s16 rangeX;
    s16 rangeY;
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
    rangeX = delta - 4;
    dead = &D_80083160;
    dirSlot = dir;
    dstY = dest->y;
    ASM_KEEP(dead);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(dir);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(dest);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    dstX = dest->x;
    if (rangeX <= 0) {
        rangeX = 1;
    }
    wx = rangeX;
    if (wx >= 5) {
        wx = 4;
    }
    rangeX = rangeX - wx;
    if (rangeX <= 0) {
        rangeX = 1;
    }

    ASM_USE_NV(dstY);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    icy = cy;
    delta2 = dstY - icy;
    if (delta2 < 0) {
        delta2 = -delta2;
    }
    rangeY = delta2 - 4;
    if (rangeY <= 0) {
        rangeY = 1;
    }
    wy = rangeY;
    if (wy >= 5) {
        wy = 4;
    }
    rangeY = rangeY - wy;
    if (rangeY <= 0) {
        rangeY = 1;
    }

    if (rnd != 0) {
        s16 r;

        r = (u16)func_800A6D30() % rangeX;
        *outX = r;
        wx = cx + r * D_8006CCD8[dir] + D_8006CCD8[dir] * wx;
        r = (u16)func_800A6D30() % rangeY;
        *outY = r;
        wy = cy + r * D_8006CCE8[dir] + D_8006CCE8[dir] * wy;
    } else {
        wx = cx + *outX * D_8006CCD8[dir] + D_8006CCD8[dir] * wx;
        wy = cy + *outY * D_8006CCE8[dir] + D_8006CCE8[dir] * wy;
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

    if (wx != dstX || wy != dstY) {
        if (D_8006CCD8[dirSlot] != 0) {
            wy = dstY;
        } else {
            wx = dstX;
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

    if (wx != dstX || wy != dstY) {
        r = func_800A07D0(cx, cy, dstX, dstY);
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
            if (ix == dstX && iy == dstY) {
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
