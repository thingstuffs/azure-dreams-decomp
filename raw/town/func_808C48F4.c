#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80000B40(M2C_UNK, void *);             /* extern */

void func_800008F4(s32 arg0, s32 arg1) {
    void *temp_a1;

    temp_a1 = (arg1 * 8) + (arg0 * 0x10);
    if (M2C_FIELD(temp_a1, s32 *, 0xDC4) & 1) {
        func_80000B40(0x107, temp_a1);
    }
}
