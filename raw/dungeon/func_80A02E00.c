#include "common.h"
#include "m2c_compat.h"

void func_80168600(void *arg0, void *arg2) {
    s16 temp_a1;
    s16 temp_v0;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 temp_a0_3;
    u8 temp_a0_4;

    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x320);
    temp_a1 = M2C_FIELD(arg0, s16 *, 0x1A);
    if (temp_a1 >= 0x33) {
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((M2C_FIELD(arg0, u8 *, 0) * (0x41 - temp_a1)) / 14);
        M2C_FIELD(arg2, u8 *, 0xD) = (u8) ((M2C_FIELD(arg0, u8 *, 1) * (0x41 - M2C_FIELD(arg0, s16 *, 0x1A))) / 14);
        M2C_FIELD(arg2, u8 *, 0xE) = (u8) ((M2C_FIELD(arg0, u8 *, 2) * (0x41 - M2C_FIELD(arg0, s16 *, 0x1A))) / 14);
    } else if (temp_a1 < 0x1A) {
        if (temp_a1 >= 0x10) {
            temp_a0 = M2C_FIELD(arg0, u8 *, 1);
            temp_a0_2 = temp_a0 + ((s32) (M2C_FIELD(arg0, u8 *, 0) - temp_a0) / (s32) (temp_a1 - 0xF));
            M2C_FIELD(arg0, u8 *, 1) = temp_a0_2;
            M2C_FIELD(arg2, u8 *, 0xD) = temp_a0_2;
            temp_a0_3 = M2C_FIELD(arg0, u8 *, 2);
            temp_a0_4 = temp_a0_3 + ((s32) (M2C_FIELD(arg0, u8 *, 0) - temp_a0_3) / (s32) (M2C_FIELD(arg0, s16 *, 0x1A) - 0xF));
            M2C_FIELD(arg0, u8 *, 2) = temp_a0_4;
            M2C_FIELD(arg2, u8 *, 0xE) = temp_a0_4;
        } else if (temp_a1 >= 8) {
            M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0) * (temp_a1 - 8)) / 8);
            M2C_FIELD(arg2, u8 *, 0xD) = (u8) ((s32) (M2C_FIELD(arg0, u8 *, 1) * (M2C_FIELD(arg0, s16 *, 0x1A) - 8)) / 8);
            M2C_FIELD(arg2, u8 *, 0xE) = (u8) ((s32) (M2C_FIELD(arg0, u8 *, 2) * (M2C_FIELD(arg0, s16 *, 0x1A) - 8)) / 8);
        } else {
            M2C_FIELD(arg0, s16 *, 0x1A) = 0;
        }
    }
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x1A) - 1;
    M2C_FIELD(arg0, s16 *, 0x1A) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
