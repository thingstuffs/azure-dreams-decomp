#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174(void *, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_800C641C();                            /* extern */

void func_800C6B44(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        func_800C641C();
        func_800C4174(arg0, arg1, arg2);
    }
}
