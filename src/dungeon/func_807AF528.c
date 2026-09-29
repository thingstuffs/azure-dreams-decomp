#include "common.h"
#include "shared/entity_objects.h"


/* Returns the direction to the target position, or 9 for a coincident position. */
s32 func_800F6D28(s16 *target_pos)
{
    if (D_80083780.x.w.i == target_pos[1]) {
        if (D_80083780.y.w.i != target_pos[3]) {
            goto compare;
        }
        return 9;
    }

compare:
    if (D_80083780.x.w.i < target_pos[1]) {
        if (D_80083780.y.w.i < target_pos[3]) {
            return 5;
        }
        if (target_pos[3] < D_80083780.y.w.i) {
            return 3;
        }
        return 4;
    }

    if (target_pos[1] < D_80083780.x.w.i) {
        if (D_80083780.y.w.i < target_pos[3]) {
            return 7;
        }
        return target_pos[3] < D_80083780.y.w.i;
    }

    if (D_80083780.y.w.i >= target_pos[3]) {
        return (target_pos[3] < D_80083780.y.w.i) * 2;
    }
    return 6;
}
