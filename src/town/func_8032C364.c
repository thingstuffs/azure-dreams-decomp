#include "common.h"
#include "m2c_compat.h"

M2C_UNK blit_nonzero_rectangle_from_table_b();                            /* extern */

/* Calls blit_nonzero_rectangle_from_table_b and returns zero. */
s32 call_state_refresh_and_return_zero(void) {
    blit_nonzero_rectangle_from_table_b();
    return 0;
}
