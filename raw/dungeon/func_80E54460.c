#include "common.h"
#include "m2c_compat.h"

void func_8015DC60(void *arg0, void *arg1, void *arg2) {
    s16 temp_v1_2;
    s32 temp_a2;
    s32 temp_v1;
    u16 temp_v0;

    temp_a2 = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a2);
    temp_v1 = M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (temp_v1 + (temp_v1 >> 5));
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_a2 + (temp_a2 >> 5));
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x20) - 1;
    M2C_FIELD(arg0, u16 *, 0x20) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
    M2C_FIELD(arg2, u16 *, 0x1C) = (u16) (M2C_FIELD(arg2, u16 *, 0x1C) + 0x80);
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x40);
    M2C_FIELD(arg2, u16 *, 0x1E) = (u16) (M2C_FIELD(arg2, u16 *, 0x1E) + 0x80);
    temp_v1_2 = ((((s32) (*(s16 *)0x80083228 + *M2C_FIELD(arg0, s16 **, 0) + 0x100) >> 9) & 7) + 2) << 9;
    M2C_FIELD(arg2, s16 *, 0x18) = temp_v1_2;
    if ((temp_v1_2 == 0x400) || (temp_v1_2 == 0xC00)) {
        M2C_FIELD(arg2, s16 *, 0x18) = (s16) (temp_v1_2 + 0x100);
    }
}
