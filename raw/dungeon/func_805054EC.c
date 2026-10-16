#include "common.h"
#include "m2c_compat.h"

s32 func_800A6D30();                                /* extern */

void func_8001CCEC(s16 arg0, u16 *arg1, u16 *arg2, void *arg3) {
    u16 var_v0;

    if (M2C_FIELD(arg3, s16 *, 0xA) == 0) {
        *arg1 = 0;
        *arg2 = 0;
        return;
    }
    if (arg0 != 2) {
        if (arg0 < 3) {
            if (arg0 != 0) {
                goto block_11;
            }
            var_v0 = M2C_FIELD(arg3, u16 *, 4);
            goto block_10;
        }
        var_v0 = -1U;
        if (arg0 != 4) {
block_11:
            *arg1 = ((s32) (func_800A6D30() & 0xFFFF) % (s32) (M2C_FIELD(arg3, u16 *, 4) - 2)) + 1;
            *arg2 = -1U;
            return;
        }
block_10:
        *arg1 = var_v0;
        *arg2 = ((s32) (func_800A6D30() & 0xFFFF) % (s32) (M2C_FIELD(arg3, u16 *, 6) - 2)) + 1;
        return;
    }
    *arg1 = ((s32) (func_800A6D30() & 0xFFFF) % (s32) (M2C_FIELD(arg3, u16 *, 4) - 2)) + 1;
    *arg2 = M2C_FIELD(arg3, u16 *, 6);
}
