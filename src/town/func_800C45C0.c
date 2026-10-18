#include "common.h"

extern s32 D_800D456C;
void find_containing_range_group(s32 value, s16 **range_groups);

/* Passes the value and shared data address to find_containing_range_group. */
void pass_value_and_range_groups(s32 value) {
    find_containing_range_group(value, &D_800D456C);
}
