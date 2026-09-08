#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A4A9C_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
} S_800A4A9C_0;   /* var_a0 in func_800A4A9C */

/* Return whether any of the four spaced status bytes is zero. */
s32 func_800A4A9C(s32 record_addr) {
    s32 status_index;
    void *status_cursor;

    status_index = 3;
    status_cursor = record_addr + 6;
loop_1:
    if (((S_800A4A9C_0 *)status_cursor)->unk_2C != 0) {
        status_index -= 1;
        status_cursor -= 2;
        if (status_index < 0) {
            return 0;
        } else {
            goto loop_1;
        }
    }
    return 1;
}
