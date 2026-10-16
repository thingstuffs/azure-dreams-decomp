#include "common.h"
#include "m2c_compat.h"

s32 func_800A41F0(void *);                          /* extern */

void *func_801688FC(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    s16 temp_v1;
    void *temp_a0;
    void *var_s0;
    void *var_v0;

    var_s0 = M2C_FIELD(arg0, s32 *, 0x5C) + 0x20;
    if (var_s0 != arg0) {
loop_2:
        temp_a0 = M2C_FIELD(var_s0, void **, -0x14);
        if ((M2C_FIELD(temp_a0, u8 *, 0x24) != (arg1 & 0xFFFF)) || (M2C_FIELD(temp_a0, u8 *, 0x25) != (arg2 & 0xFFFF)) || (temp_v1 = M2C_FIELD(var_s0, s16 *, 0x88), (((arg3 + 0x20) < temp_v1) != 0)) || (temp_v1 < (arg3 - 0x20)) || ((u32) (M2C_FIELD(var_s0, u8 *, 0x13) - 0x33) < 4U) || (var_v0 = var_s0 - 0x20, ((func_800A41F0(var_s0) << 0x10) == 0))) {
            var_s0 = M2C_FIELD(var_s0, s32 *, 0x5C) + 0x20;
            if (var_s0 == arg0) {
                goto block_9;
            }
            goto loop_2;
        }
    } else {
block_9:
        var_v0 = NULL;
    }
    return var_v0;
}
