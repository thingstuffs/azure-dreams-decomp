#include "common.h"

#include "sdk/abs.h"
/* Returns the Chebyshev distance between two byte-sized coordinate pairs. */
s16 get_byte_coordinate_chebyshev_distance(s32 start_x, s32 start_y, s32 end_x, s32 end_y) {
    end_x &= 0xFF;
    start_x &= 0xFF;
    end_x -= start_x;
    end_x = abs(end_x);
    end_y &= 0xFF;
    start_y &= 0xFF;
    end_y -= start_y;
    end_y = abs(end_y);
    if (end_x < end_y) {
        return end_y;
    }
    return end_x;
}
