#include "common.h"
#include "town/scene.h"

s32 is_pair_result_valid_b(s32 grid_y, s32 grid_x);                /* extern */

/* Return whether func_80017B98 reports zero for (0xD, 2). */
s32 is_check_d_2_zero(void) {
    return is_pair_result_valid_b(0xD, 2) == 0;
}
