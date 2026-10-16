#include "common.h"

extern s32 townGetScriptFlagMask(s32);

/* Builds a bitmask of nonzero query results for consecutive indices. */
s32 townReadScriptFlagRange(s32 start_index, s32 count) {
    s32 offset;
    s32 mask;

    offset = 0;
    mask = 0;
    if (count > 0) {
        do {
            if (townGetScriptFlagMask(start_index + offset) != 0) {
                mask += 1 << offset;
            }
            offset++;
        } while (offset < count);
    }
    return mask;
}
