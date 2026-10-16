#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_801621D0(void *, M2C_UNK, s32);        /* extern */

void func_80162318(void *arg0) {
    s16 temp_a0;
    s16 temp_v0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s16 *, 0x1A);
    if (temp_a0 >= 0x10) {
        var_v0 = 0x10;
    } else {
        var_v0 = (((0xF - temp_a0) * 6) + 0x10) & 0xFF;
    }
    func_801621D0(arg0, 0x70, var_v0);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x1A) - 1;
    M2C_FIELD(arg0, s16 *, 0x1A) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
