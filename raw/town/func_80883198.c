#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700BD8(M2C_UNK, s32);                /* extern */

void func_80700998(s32 arg0, s32 arg1) {
    s32 temp_a1;

    temp_a1 = (arg1 * 8) + (arg0 * 0x10);
    if (M2C_FIELD((temp_a1 + 0x80700000), s32 *, 0x734) & 1) {
        func_80700BD8(0x107, temp_a1);
    }
}
