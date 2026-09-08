#include "common.h"

extern s32 func_8001ADE0(s32);

/* Builds a bitmask of nonzero query results for consecutive indices. */
s32 func_8001B0E8(s32 start_index, s32 count) {
    s32 offset;
    s32 mask;

    offset = 0;
    mask = 0;
    if (count > 0) {
        do {
            if (func_8001ADE0(start_index + offset) != 0) {
                mask += 1 << offset;
            }
            offset++;
        } while (offset < count);
    }
    return mask;
}
