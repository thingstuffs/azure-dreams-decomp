#include "common.h"

s16 ratan2();              /* extern */

/* Returns ratan2 of the Y and X differences between the two planar positions. */
s16 calculate_planar_heading(s16 start_x, s16 start_y, s16 end_x, s16 end_y) {
    return ratan2(end_y - start_y, end_x - start_x, end_x, end_y);
}
