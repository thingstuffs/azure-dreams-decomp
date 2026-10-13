#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef struct {
    s16 x;
    s16 y;
    s16 unk4;
    s16 dir;
} Pos;
typedef u32 CoordPair __attribute__((aligned(2)));

typedef struct {
    s16 unused[10];
    s16 stride;
} DungeonState;

typedef struct {
    s16 kind;
    s16 value;
    s16 flags;
} DungeonCell;

extern DungeonCell D_800EA000[];

extern s32 func_800A6D30(void);
extern u32 func_800A07D0(s16 x0, s16 y0, s16 x1, s16 y1);

/* Pick the next step toward the destination, wandering around blocked tiles with a random tie-break. */
s32 func_8001C06C(Pos *start, Pos *dest, s16 rnd, s16 *outX, s16 *outY) {
    s16 count;
    s16 cx;
    s16 cy;
    s32 dir;
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
    DungeonState *st;

    count = 0;
    cy = start->y;
    cx = start->x;
    delta2 = cx;
    delta = (s32)(*(CoordPair *)dest << 16) >> 16;
    delta = delta - delta2;
    dir = (u16)start->dir;
    delta = __builtin_abs(delta);
    rangeX = delta - 4;
    delta2 = (s32)&gameWork;
    dirSlot = dir;
    dstY = dest->y;
    st = (DungeonState *)((u8 *)delta2 + 476);
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

    icy = dstY;
    rangeY = __builtin_abs(icy - cy) - 4;
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
        wx = cx + rr * dirStepX[(s16)dir] + dirStepX[(s16)dir] * wx;
        rr = (u16)func_800A6D30() % rangeY;
        *outY = rr;
        wy = cy + rr * dirStepY[(s16)dir] + dirStepY[(s16)dir] * wy;
    } else {
        wx = cx + *outX * dirStepX[(s16)dir] + dirStepX[(s16)dir] * wx;
        wy = cy + *outY * dirStepY[(s16)dir] + dirStepY[(s16)dir] * wy;
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
        cx += dirStepX[(s16)dir];
        cy += dirStepY[(s16)dir];
    }

    if (wx != dstX || wy != dstY) {
        if (dirStepX[dirSlot] != 0) {
            wy = dstY;
        } else {
            wx = dstX;
        }
        delta = func_800A07D0(cx, cy, wx, wy);
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
            cx += dirStepX[((u32)delta >> 9) & 6];
            cy += dirStepY[((u32)delta >> 9) & 6];
        }
    }

    if (wx != dstX || wy != dstY) {
        delta = func_800A07D0(cx, cy, dstX, dstY);
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
            cx += dirStepX[((u32)delta >> 9) & 6];
            cy += dirStepY[((u32)delta >> 9) & 6];
        }
    }
    return count;
}
