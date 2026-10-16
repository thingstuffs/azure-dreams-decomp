#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800CA88C();                            /* extern */

void func_800CA40C(void *arg0) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800CA88C();
        M2C_FIELD(arg0, s16 *, 0x72) = 0;
    }
}
