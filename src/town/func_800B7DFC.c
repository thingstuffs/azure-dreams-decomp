#include "common.h"

/* Return 0 if equal, 3 if left is greater, or 4 if left is less. */
s32 func_800B555C(s32 left, s32 right) {
    s32 result;

    result = 0;
    if (left != right) {
        result = 3;
        if (left < right) {
            result = 4;
        }
    }
    return result;
}
