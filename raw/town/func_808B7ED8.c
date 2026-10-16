#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80003BCC(M2C_UNK, void *);             /* extern */

void func_800036D8(s32 arg0, s32 arg1) {
    void *temp_a1;

    temp_a1 = (arg1 * 8) + (arg0 << 5);
    if (M2C_FIELD(temp_a1, s32 *, 0x3FB8) & 1) {
        func_80003BCC(0x1F9, temp_a1);
    }
}
