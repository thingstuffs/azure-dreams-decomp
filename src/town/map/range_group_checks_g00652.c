/* Finds the range group containing a value and checks values against the current town range table. */
/* inferred-strong G00652: range_group_checks_g00652; joins CL:town/func_800C4508; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C4508. */
#include "town/map/range_group_checks_g00652.h"

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

/* Passes the value and shared data address to find_containing_range_group. */
void pass_value_and_range_groups(s32 value) {
    find_containing_range_group(value, (s16 **)&D_800D456C);
}

/* Checks a masked value against the table selected by the current state. */
s32 check_masked_value_in_current_range(s32 value) {
    s8 *state;
    s32 result;

    state = (s8 *)&map_runtime_state;
    value &= 0x3FFF;
    if (*(s16 *)(state + 0x18) != 0xC) {
        return find_containing_range_group(value, (s16 * *)(&D_800D4640));
    }
    if (*(s16 *)(state + 0x1A) == 0xD) {
        if (find_containing_range_group(value, (s16 * *)(&D_800D4658)) != 0) {
            return 6;
        }
    } else if (*(s16 *)(state + 0x1A) == 0x2A) {
        if (find_containing_range_group(value, (s16 * *)(&D_800D4660)) != 0) {
            return 7;
        }
    }
    result = 0;
    return result;
}
