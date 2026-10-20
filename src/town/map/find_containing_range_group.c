#include "common.h"

/* Returns the first range group containing value as a one-based index, or zero if none. */
s32 find_containing_range_group(s32 value, s16 **range_groups)
{
    s32 group_index;
    s32 range_index;

    for (group_index = 0; range_groups[group_index] != 0; group_index++) {
        for (range_index = 0; range_groups[group_index][range_index * 2] != -1; range_index++) {
            if (value >= range_groups[group_index][range_index * 2] &&
                range_groups[group_index][range_index * 2 + 1] >= value) {
                return group_index + 1;
            }
        }
    }
    return 0;
}
