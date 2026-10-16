#include "common.h"
#include "m2c_compat.h"

void func_80000B90(s32 arg0) {
    s32 *temp_v1;
    s32 temp_v0;
    s32 var_v0;

    if (arg0 != 1) {
        var_v0 = arg0;
        if (arg0 < 0) {
            var_v0 = arg0 + 0x1F;
        }
        temp_v0 = var_v0 >> 5;
        temp_v1 = (temp_v0 * 4) + *(s32 *)0xE54;
        *temp_v1 &= ~(1 << (arg0 - (temp_v0 << 5)));
    }
}
