/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"

s16 evaluate_summed_position_minus_y_offset();               

/* Returns the lowest surface sample after removing each Y offset, or 0x7FFF when no lower sample is found. */
s16 find_minimum_sampled_position(s32 context, s32 data, s32 count) {
    s16 value;
    s16 minimum;
    s32 index;

    minimum = 0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = evaluate_summed_position_minus_y_offset(context, data, index);
            if ((value << 0x10) < (minimum << 0x10)) {
                minimum = value;
            }
            index += 1;
        } while (index < count);
    }
    return minimum;
}
