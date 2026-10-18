#include "common.h"

s16 adjust_summed_vector_by_entry_component();

/* Return the maximum sampled value across position offsets, with a minimum of zero. */
s16 get_maximum_sampled_offset_value(s32 base_position, s32 offsets, s32 offset_count) {
    s16 sample_value;
    s16 max_value;
    s32 offset_index;

    max_value = 0;
    offset_index = 0;
    if (offset_count > 0) {
        do {
            sample_value = adjust_summed_vector_by_entry_component(base_position, offsets, offset_index);
            if ((sample_value << 0x10) > (max_value << 0x10)) {
                max_value = sample_value;
            }
            offset_index += 1;
        } while (offset_index < offset_count);
    }
    return max_value;
}
