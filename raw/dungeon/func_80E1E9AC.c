#include "common.h"
#include "m2c_compat.h"

s32 func_800A48F0(void *, M2C_UNK, s8);             /* extern */
s32 func_800A6D30(s32);                             /* extern */

s32 func_8016A1AC(void *arg0) {
    s32 temp_a0;
    s32 var_v0;
    s32 var_v0_2;
    u8 temp_v1;

    if (arg0 != *(s32 *)0x800E3D7C) {
        temp_v1 = M2C_FIELD(arg0, u8 *, 3);
        temp_a0 = func_800A6D30() & 0xFFFF;
        if (temp_v1 != 0) {
            var_v0_2 = temp_a0 % (s32) temp_v1;
        } else {
            var_v0_2 = 0;
        }
        if ((var_v0_2 >= 0x10) || (var_v0 = 1, (func_800A48F0(arg0, 0x19, (s8) (((u8) M2C_FIELD(arg0, u8 *, 0x11) >> 2) + 0x20 + (func_800A6D30(temp_a0) & 3))) & 0x8000))) {
            goto block_6;
        }
    } else {
block_6:
        var_v0 = 0;
    }
    return var_v0;
}
