#include "common.h"
#include "m2c_compat.h"

void *func_80156A00(void *arg0, s32 arg1, s32 arg2, s16 arg3) {
    s16 temp_v1_2;
    void *temp_v1;
    void *var_a0;
    void *var_v0;

    var_a0 = M2C_FIELD(arg0, s32 *, 0x5C) + 0x20;
    if (var_a0 != arg0) {
loop_2:
        temp_v1 = M2C_FIELD(var_a0, void **, -0x14);
        if ((M2C_FIELD(temp_v1, u8 *, 0x24) != (arg1 & 0xFFFF)) || (M2C_FIELD(temp_v1, u8 *, 0x25) != (arg2 & 0xFFFF)) || (temp_v1_2 = M2C_FIELD(var_a0, s16 *, 0x88), (((arg3 + 0x20) < temp_v1_2) != 0)) || (temp_v1_2 < (arg3 - 0x20)) || (var_v0 = var_a0 - 0x20, (((u32) (M2C_FIELD(var_a0, u8 *, 0x13) - 0x33) < 4U) == 0))) {
            var_a0 = M2C_FIELD(var_a0, s32 *, 0x5C) + 0x20;
            if (var_a0 == arg0) {
                goto block_8;
            }
            goto loop_2;
        }
    } else {
block_8:
        var_v0 = NULL;
    }
    return var_v0;
}
