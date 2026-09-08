#include "common.h"

/* Moves an index by a step, clamps in the step direction, and returns zero for an empty range. */
s32 func_80049E1C(s32 index, s32 step, s32 count)
{
    s32 result;
    s32 clamped_index;

    result = index;
    if (count != 0) {
        result += step;
        if (step >= 0) {
            index = result;
            count -= 1;
            if (index >= count) {
                index = count;
            }
            result = index;
        } else {
            clamped_index = result;
            if (result < 0) {
                clamped_index = 0;
            }
            result = clamped_index;
        }
    } else {
        result = 0;
    }

    return result;
}
