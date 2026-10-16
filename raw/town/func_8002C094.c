#include "common.h"
#include "m2c_compat.h"

s32 func_800C30E0();                                /* extern */
M2C_UNK func_800C9DB8(void *, M2C_UNK, M2C_UNK);    /* extern */

void func_800C97F4(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    if (func_800C30E0() == 0) {
        temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
        M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            func_800C9DB8(arg0, arg1, arg2);
        }
    }
}
