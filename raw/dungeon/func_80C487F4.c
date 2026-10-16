#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(M2C_UNK);                     /* extern */

void func_8016DFF4(void *arg0, void *arg1, M2C_UNK arg2) {
    u16 temp_v0;

    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + 0x10000);
    func_800478B8(arg2);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x1A) - 1;
    M2C_FIELD(arg0, u16 *, 0x1A) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
