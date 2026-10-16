#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033D08();                            /* extern */

void func_800B9F74(void *arg0, void *arg2) {
    if (*M2C_FIELD(arg0, u8 **, 0x98) == 0) {
        func_80033D08();
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + (s8) M2C_FIELD(M2C_FIELD(arg0, void **, 0x9C), u8 *, 0x97));
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) & 0xFFF);
}
