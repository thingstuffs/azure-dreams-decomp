/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"

extern s16 adjust_summed_vector_by_entry_component(s32, s32, s32);

s16 get_maximum_sampled_offset_value(s32 lookup_a, s32 lookup_b, s32 count) {
    s16 value;
    s16 max_value;
    s32 index;

    max_value = 0;
    index = 0;
    if (count > 0) {
        do {
            value = adjust_summed_vector_by_entry_component(lookup_a, lookup_b, index);
            if ((value << 0x10) > (max_value << 0x10)) {
                max_value = value;
            }
            index += 1;
        } while (index < count);
    }
    return max_value;
}
