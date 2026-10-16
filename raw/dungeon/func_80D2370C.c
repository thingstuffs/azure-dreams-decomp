#include "common.h"
#include "m2c_compat.h"

void func_8015EF0C(void *arg0, void *arg1) {
    s16 temp_v0;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;

    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg0, s32 *, 0x40));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg0, s32 *, 0x44));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg0, s32 *, 0x48));
    temp_a2 = (s32) (M2C_FIELD(arg0, u8 *, 0) * M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34);
    temp_a1 = (s32) (M2C_FIELD(arg0, u8 *, 1) * M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34);
    temp_a0 = (s32) (M2C_FIELD(arg0, u8 *, 2) * M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34);
    M2C_FIELD(arg0, s32 *, 0x48) = (s32) (M2C_FIELD(arg0, s32 *, 0x48) + M2C_FIELD(arg0, s32 *, 0x54));
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 1;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    M2C_FIELD(arg0, s8 *, 4) = (s8) temp_a2;
    M2C_FIELD(arg0, s8 *, 5) = (s8) temp_a1;
    M2C_FIELD(arg0, s8 *, 6) = (s8) temp_a0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s8 *, 4);
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
