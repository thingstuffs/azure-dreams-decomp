#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047454(void *, s16);                 /* extern */

void func_80169D44(void *arg0, void *arg1, void *arg2) {
    s16 temp_a1;
    s32 temp_lo;
    u16 temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0xAC);
    M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_v1, u16 *, 2);
    M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_v1, u16 *, 6);
    M2C_FIELD(arg1, u16 *, 0xA) = (u16) M2C_FIELD(temp_v1, u16 *, 0xA);
    temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x320;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
    temp_a1 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    temp_lo = (s32) (temp_a1 * 0x50) / (s16) M2C_FIELD(arg0, s16 *, 0xA8);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) temp_a1;
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
    func_80047454(arg2, temp_a1);
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800803D4 |= 0x8000;
    }
}
