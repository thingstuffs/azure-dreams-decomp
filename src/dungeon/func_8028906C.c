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

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern DungeonCell D_800EA000[];
extern u8 D_80083160[];

extern s32 func_800A6D30(void);
extern u32 func_800A07D0(s16 x0, s16 y0, s16 x1, s16 y1);

s32 func_8001C06C(Pos *start, Pos *dest, s16 rnd, s16 *outX, s16 *outY) {
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

    count = 0;
    cy = start->y;
    delta2 = start->x;
    cx = delta2;
    delta = dest->x;
    delta = delta - delta2;
    dir = start->dir;
    ASM_USE2_NV(delta2, cx);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (delta < 0) {
        delta = -delta;
    }
    rangeX = delta - 4;
    ASM_SET(dead);   /* MATCH pin: retail schedule: same instructions, different order without it */
    dead = (DungeonState *)D_80083160;
    dirSlot = dir;
    dstY = dest->y;
    st = (DungeonState *)((u8 *)dead + 476);
    ASM_KEEP_NV(dir);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_KEEP_NV(dest);   /* MATCH pin: keeps a statement from moving across a call/branch */
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

    ASM_USE_NV(dstY);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
        s16 rr;

        rr = (u16)func_800A6D30() % rangeX;
        *outX = rr;
        wx = cx + rr * D_8006CCD8[dir] + D_8006CCD8[dir] * wx;
        rr = (u16)func_800A6D30() % rangeY;
        *outY = rr;
        wy = cy + rr * D_8006CCE8[dir] + D_8006CCE8[dir] * wy;
    } else {
        wx = cx + *outX * D_8006CCD8[dir] + D_8006CCD8[dir] * wx;
        wy = cy + *outY * D_8006CCE8[dir] + D_8006CCE8[dir] * wy;
    }

    for (;;) {
        s32 ix;
        s32 iy;

        iy = cy;
        ix = cx;
        D_800EA000[(iy << st->stride) + ix].kind = 104;
        D_800EA000[(iy << st->stride) + ix].flags = 1;
        if (ix == wx && iy == wy) {
            break;
        }
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
            s32 ix;
            s32 iy;

            iy = cy;
            ix = cx;
            D_800EA000[(iy << st->stride) + ix].kind = 104;
            D_800EA000[(iy << st->stride) + ix].flags = 1;
            if (ix == wx && iy == wy) {
                break;
            }
            count++;
            cx += D_8006CCD8[(r >> 9) & 6];
            cy += D_8006CCE8[(r >> 9) & 6];
        }
    }

    if (wx != dstX || wy != dstY) {
        r = func_800A07D0(cx, cy, dstX, dstY);
        for (;;) {
            s32 ix;
            s32 iy;

            iy = cy;
            ix = cx;
            D_800EA000[(iy << st->stride) + ix].kind = 104;
            D_800EA000[(iy << st->stride) + ix].flags = 1;
            if (ix == dstX && iy == dstY) {
                break;
            }
            count++;
            cx += D_8006CCD8[(r >> 9) & 6];
            cy += D_8006CCE8[(r >> 9) & 6];
        }
    }
    return count;
}
