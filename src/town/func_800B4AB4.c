#include "common.h"

/* Return the first matching value index, or the number of entries searched. */
s32 func_800B2214(s32 *values, s32 target_value, s32 count) {
    s32 *current_value;
    s32 index;

    current_value = values;
    index = 0;
    while (index < count && target_value != *current_value) {
        index += 1;
        current_value += 1;
    }
    return index;
}
