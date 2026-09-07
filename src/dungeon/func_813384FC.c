#include "common.h"

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s32 unk8;
} DungeonPoint;

extern DungeonPoint D_80083780;

s32 func_8016F4FC(DungeonPoint *arg0)
{
    DungeonPoint *point;

    if (D_80083780.x == arg0->x && D_80083780.y == arg0->y) {
        return 9;
    }

    point = &D_80083780;
    if (point->x < arg0->x) {
        if (point->y < arg0->y) {
            return 1;
        }
        if (arg0->y < point->y) {
            return 7;
        }
        return 0;
    }

    if (arg0->x < point->x) {
        if (point->y < arg0->y) {
            return 3;
        }
        if (arg0->y < point->y) {
            return 5;
        }
        return 4;
    }

    if (point->y < arg0->y) {
        return 2;
    }
    if (arg0->y < point->y) {
        return 6;
    }
    return 0;
}

/* MECHANISM: Recover the true-space local return joins as ordinary returns in a
   frameless leaf; keep a named global-point base for the post-equality regions.
   The initial equality remains a direct global comparison. */
