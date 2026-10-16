#include "common.h"
#include "m2c_compat.h"

void func_80003BCC(s32 arg0) {
    s32 *temp_a0;
    s32 temp_v1;
    s32 var_v1;

    if (arg0 != 0) {
        var_v1 = arg0;
        if (arg0 < 0) {
            var_v1 = arg0 + 0x1F;
        }
        temp_v1 = var_v1 >> 5;
        temp_a0 = (temp_v1 * 4) + *(s32 *)0x45FC;
        *temp_a0 |= 1 << (arg0 - (temp_v1 << 5));
    }
}
