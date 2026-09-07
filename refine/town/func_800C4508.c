#include "common.h"

/* Returns the first range group containing value as a one-based index, or zero if none. */
s32 func_800C1C68(s32 value, s16 **range_groups)
{
    s16 **group;
    s16 *ranges;
    s16 *range;
    s32 group_index;
    s32 return_value;
    s32 group_number;
    s32 range_offset;
    s32 empty_marker;
    s32 end_marker;

    if (*range_groups == 0) {
        goto not_found;
    }

    group_index = 0;
    empty_marker = -1;
    group = range_groups;
    ranges = *(s16 * volatile *)group;

group_loop:
    if (*ranges != empty_marker) {
        group_number = group_index + 1;
        end_marker = -1;
        range_offset = 0;

range_loop:
        ranges = *(s16 * volatile *)group;
        range = (s16 *)(range_offset + (s32)ranges);
        if (value < range[0]) {
            goto advance;
        }
        if (range[1] < value) {
            goto advance;
        }
        return_value = group_number;
        goto done;

advance:
        ranges = range_groups[group_index];
        range_offset += 4;
        return_value = range_offset + (s32)ranges;
        return_value = *(s16 *)return_value;
        ASM_KEEP(return_value);   /* MATCH pin: retail register colouring depends on it */
        if (return_value != end_marker) {
            goto range_loop;
        }
    }

    group++;
    ranges = *group;
    group_index++;
    if (ranges != 0) {
        goto group_loop;
    }

not_found:
    return_value = 0;
done:
    ASM_KEEP(return_value);   /* MATCH pin: retail register colouring depends on it */
    return return_value;
}
