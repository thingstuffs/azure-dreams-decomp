#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800478B8(void *, s32, void *);         /* extern */

void func_8016E0FC(void *arg0, void *arg1, void *arg2) {
    s32 temp_a2;
    u16 temp_v0;

    M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0xA4));
    temp_a2 = M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + temp_a2);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
    func_800478B8(arg2, temp_a2, arg0);
}
