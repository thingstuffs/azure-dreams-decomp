#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_800814A0[3];
s32 func_800644B8(s32);

void func_81910844(void *arg0, void *arg1, void *arg2) {
    s32 temp_v0;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_a1;
    s32 temp_a0_2;
    u16 temp_v0_2;
    u16 temp_v1_2;
    s16 temp_v1_5;
    s16 temp_v0_3;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) =
        (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    M2C_FIELD(arg0, u16 *, 6) =
        (u16) (M2C_FIELD(arg0, u16 *, 6) + 1);
    temp_v0 = M2C_FIELD(arg1, s32 *, 0);
    temp_v1_4 = M2C_FIELD(arg1, s32 *, 0xC);
    temp_v1_3 = M2C_FIELD(arg1, s32 *, 4);
    temp_a1 = M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = temp_v0 + temp_v1_4;
    M2C_FIELD(arg1, s32 *, 4) = temp_v1_3 + temp_a1;
    M2C_FIELD(arg0, s32 *, 0xC) =
        M2C_FIELD(arg0, s32 *, 0xC) + M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 8) =
        M2C_FIELD(arg0, s32 *, 0xC) -
        ((func_800644B8((0x800 / (s16) M2C_FIELD(arg0, s16 *, 8)) *
                       (s16) M2C_FIELD(arg0, u16 *, 6)) >> 4) << 0xE);
    temp_a0_2 = 0x200 / (s16) M2C_FIELD(arg0, s16 *, 8);
    temp_v0_2 = M2C_FIELD(arg2, u16 *, 0x1A);
    temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x1E);
    M2C_FIELD(arg2, u16 *, 0x1A) = temp_v0_2 + 0x300;
    temp_v1_2 = temp_v1_2 - temp_a0_2;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v1_2;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v1_2;
    temp_v1_5 = M2C_FIELD(arg0, s16 *, 6);
    temp_v0_3 = M2C_FIELD(arg0, s16 *, 8);
    if (temp_v1_5 > temp_v0_3) {
        M2C_FIELD(arg0, u16 *, -2) =
            M2C_FIELD(arg0, u16 *, -2) | 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
