#include "common.h"
#include "town/map.h"

s16 evaluate_summed_vector_minus_base();               /* extern */

/* Returns the minimum indexed value, or 0x7FFF if the count is nonpositive. */
s16 min_indexed_query(s32 context, s32 data, s32 count) {
    s16 value;
    s16 minimum;
    s32 index;

    minimum = 0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = evaluate_summed_vector_minus_base(context, data, index);
            if ((value << 0x10) < (minimum << 0x10)) {
                minimum = value;
            }
            index += 1;
        } while (index < count);
    }
    return minimum;
}
