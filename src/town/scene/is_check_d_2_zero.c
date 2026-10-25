#include "common.h"

s32 func_80017B98(s32 grid_y, s32 grid_x);                /* extern */

/* Return whether func_80017B98 reports zero for (0xD, 2). */
s32 is_check_d_2_zero(void) {
    return func_80017B98(0xD, 2) == 0;
}
