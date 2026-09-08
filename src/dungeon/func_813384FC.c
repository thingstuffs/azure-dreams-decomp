#include "common.h"

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s32 unk8;
} DungeonPoint;

extern DungeonPoint D_80083780;

/* Return the direction from the global point to the target, or 9 if coincident. */
s32 func_8016F4FC(DungeonPoint *target)
{
    DungeonPoint *origin;

    if (D_80083780.x == target->x && D_80083780.y == target->y) {
        return 9;
    }

    origin = &D_80083780;
    if (origin->x < target->x) {
        if (origin->y < target->y) {
            return 1;
        }
        if (target->y < origin->y) {
            return 7;
        }
        return 0;
    }

    if (target->x < origin->x) {
        if (origin->y < target->y) {
            return 3;
        }
        if (target->y < origin->y) {
            return 5;
        }
        return 4;
    }

    if (origin->y < target->y) {
        return 2;
    }
    if (target->y < origin->y) {
        return 6;
    }
    return 0;
}
