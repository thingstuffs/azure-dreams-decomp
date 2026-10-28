#include "common.h"
#include "town/player/position_upper_bound_g00540.h"

s16 query_offset_position_minus_z();               /* extern */

/* Returns the maximum evaluated value across count entries, starting at -0x7FFF. */
s16 max_adjusted_z_query(LocalVec *context, s32 data, s32 count) {
    s16 value;
    s16 max_value;
    s32 index;

    max_value = -0x7FFF;
    index = 0;
    if (count > 0) {
        do {
            value = query_offset_position_minus_z(context, data, index);
            if ((value << 0x10) > (max_value << 0x10)) {
                max_value = value;
            }
            index += 1;
        } while (index < count);
    }
    return max_value;
}
