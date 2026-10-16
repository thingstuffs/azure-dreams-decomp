#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C4174();                            /* extern */

void func_800CA094(void *arg0) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x6C) - 1;
    M2C_FIELD(arg0, u16 *, 0x6C) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, 0x72) = (u16) M2C_FIELD(arg0, u16 *, 0x6E);
        func_800C4174();
    }
}
