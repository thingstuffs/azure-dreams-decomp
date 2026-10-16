#include "common.h"
#include "m2c_compat.h"

void func_80175878(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0;
    s32 temp_a0;
    u8 temp_a0_2;

    M2C_FIELD(arg1, s16 *, 2) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 2) + ((s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 2) - M2C_FIELD(arg1, s16 *, 2)) / (s16) M2C_FIELD(arg0, s16 *, 0xC)));
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 6) + ((s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 6) - M2C_FIELD(arg1, s16 *, 6)) / (s16) M2C_FIELD(arg0, s16 *, 0xC)));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg1, s16 *, 0xA) + ((s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xA) - M2C_FIELD(arg1, s16 *, 0xA)) / (s16) M2C_FIELD(arg0, s16 *, 0xC)));
    temp_a0 = M2C_FIELD(arg2, u8 *, 0xE) | (M2C_FIELD(arg2, u8 *, 0xC) | M2C_FIELD(arg2, u8 *, 0xD));
    temp_a0_2 = temp_a0 + ((s32) (0xC0 - temp_a0) / (s16) M2C_FIELD(arg0, s16 *, 0xC));
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 1) {
        M2C_FIELD(arg2, u8 *, 0xC) = temp_a0_2;
    }
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 2) {
        M2C_FIELD(arg2, u8 *, 0xE) = temp_a0_2;
    }
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 *, 0x14) & 4) {
        M2C_FIELD(arg2, u8 *, 0xD) = temp_a0_2;
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - 1;
    M2C_FIELD(arg0, s16 *, 0xC) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
