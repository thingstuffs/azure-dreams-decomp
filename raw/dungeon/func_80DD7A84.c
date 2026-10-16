#include "common.h"
#include "m2c_compat.h"

void func_80153284(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x24) - 1;
    M2C_FIELD(arg0, u16 *, 0x24) = temp_v0;
    if ((s16) temp_v0 < 8) {
        M2C_FIELD(arg0, u16 *, 0x4E) = (u16) (M2C_FIELD(arg0, u16 *, 0x4E) - 1);
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x4E) < 2) {
        M2C_FIELD(arg0, u16 *, 0x4E) = 2U;
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x24) < 0xA) {
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x2A) + 1;
        M2C_FIELD(arg0, u16 *, 0x2A) = temp_v0_2;
        M2C_FIELD(arg0, u16 *, 0x50) = (u16) (M2C_FIELD(arg0, u16 *, 0x50) + temp_v0_2);
    } else {
        M2C_FIELD(arg0, u16 *, 0x50) = (u16) (M2C_FIELD(arg0, u16 *, 0x50) + 1);
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x24) < 0xB) {
        temp_v1 = M2C_FIELD(arg0, u16 *, 0x2C) + 2;
        M2C_FIELD(arg0, u16 *, 0x2C) = temp_v1;
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) - temp_v1);
    }
    temp_a0 = (s16) M2C_FIELD(arg0, u16 *, 0x24);
    if (temp_a0 < 5) {
        M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((M2C_FIELD(arg0, u8 *, 2) * temp_a0) / 5);
        M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((M2C_FIELD(arg0, u8 *, 3) * (s16) M2C_FIELD(arg0, u16 *, 0x24)) / 5);
        M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((M2C_FIELD(arg0, u8 *, 4) * (s16) M2C_FIELD(arg0, u16 *, 0x24)) / 5);
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x24) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
