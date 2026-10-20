#include "common.h"

extern s32 get_script_flag_mask(s32);

/* Builds a bitmask of nonzero query results for consecutive indices. */
s32 read_script_flag_range(s32 start_index, s32 count) {
    s32 offset;
    s32 mask;

    offset = 0;
    mask = 0;
    if (count > 0) {
        do {
            if (get_script_flag_mask(start_index + offset) != 0) {
                mask += 1 << offset;
            }
            offset++;
        } while (offset < count);
    }
    return mask;
}
