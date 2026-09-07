#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8002527C(void) __attribute__((noreturn));
extern void func_800252E8(void) __attribute__((noreturn));
extern s32 func_80025604();
extern s32 func_80026384();

extern u16 D_800281F8[];
extern u8 D_80028220[];
extern s32 D_800814A0[];
extern void *D_800E3D7C[];

void func_819598B4(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0_3;
    s16 temp_a1;
    s32 temp_x;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    u16 temp_v1_2;
    s32 temp_a0;
    s32 temp_a0_2;
    u8 temp_v0_3;
    u8 temp_v1_3;

    D_800281F8[0]++;
    temp_v1 = FIELD(arg0, s16, 0x2C);
    if (temp_v1 == 1) {
        goto state_1;
    }
    if (temp_v1 >= 2) {
        goto state_ge_2;
    }
    if (temp_v1 == 0) {
        goto state_0;
    }
    func_800252E8();
    return;

state_ge_2:
    if (temp_v1 == 2) {
        goto state_2;
    }
    func_800252E8();
    return;

state_0:
    temp_v1_2 = FIELD(arg2, u16, 0x1E);
    temp_a0 = FIELD(arg2, u8, 0xC);
    FIELD(arg2, u16, 0x1E) = (u16)(temp_v1_2 + ((s32)(0x1000 - temp_v1_2) / FIELD(arg0, s16, 0x30)));
    temp_x = 0x80 - temp_a0;
    temp_a1 = FIELD(arg0, s16, 0x3C);
    temp_a0_2 = temp_a0 + ((temp_x - temp_a1) / FIELD(arg0, s16, 0x30));
    FIELD(arg2, u8, 0xC) = temp_a0_2;
    FIELD(arg2, u8, 0xD) = temp_a0_2;
    FIELD(arg2, u8, 0xE) = temp_a0_2;
    FIELD(arg1, s16, 2) = (s16)((u16)FIELD(arg1, s16, 2) + ((s32)(FIELD(arg0, s16, 0x14) - FIELD(arg1, s16, 2)) / FIELD(arg0, s16, 0x30)));
    FIELD(arg1, s16, 6) = (s16)((u16)FIELD(arg1, s16, 6) + ((s32)(FIELD(arg0, s16, 0x16) - FIELD(arg1, s16, 6)) / FIELD(arg0, s16, 0x30)));
    temp_a0_3 = FIELD(arg1, s16, 0xA);
    FIELD(arg1, s16, 0xA) = (s16)(FIELD(arg1, volatile u16, 0xA) + ((s32)(FIELD(arg0, s16, 0x18) - temp_a0_3) / FIELD(arg0, s16, 0x30)));
    temp_v0 = (u16)FIELD(arg0, s16, 0x30) - 1;
    FIELD(arg0, s16, 0x30) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto common;
    }
    FIELD(arg0, s16, 0x30) = 0x10;
    FIELD(arg2, u16, 0x1E) = 0x1000;
    FIELD(arg2, u32, 0xC) = 0x00808080;
    if (FIELD(arg0, s16, 0x3C) != 0) {
        FIELD(arg0, s16, 0x2C) = 2;
        func_800252E8();
    }
    {
        u32 tailslot;

        tailslot = FIELD(arg0, u16, 0x2C) + 1;
        ASM_TAILSLOT_PIN(tailslot);
        func_8002527C();
    }

state_1:
    if (FIELD(arg0, s16, 0x38) != 0) {
        goto finish_state_1;
    }
    if (func_80026384(FIELD(arg0, s16, 0x1C), FIELD(arg0, s16, 0x1E), FIELD(arg0, s16, 0x20), FIELD(D_800E3D7C[0], s16, 0x2A)) == 0) {
        goto common;
    }
    func_80025604(FIELD(arg0, s16, 0x1C), FIELD(arg0, s16, 0x1E), FIELD(arg0, s16, 0x20));
finish_state_1:
    FIELD(arg0, s16, 0x30) = 0x10;
    FIELD(arg0, s16, 0x2C)++;
    func_800252E8();
    return;

state_2:
    temp_v1_3 = FIELD(arg2, u8, 0xC);
    temp_v1_3 -= (s32)temp_v1_3 / FIELD(arg0, s16, 0x30);
    FIELD(arg2, u8, 0xC) = temp_v1_3;
    FIELD(arg2, u8, 0xD) = temp_v1_3;
    FIELD(arg2, u8, 0xE) = temp_v1_3;
    temp_v0_2 = (u16)FIELD(arg0, s16, 0x30) - 1;
    FIELD(arg0, s16, 0x30) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto common;
    }
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;

common:
    if (FIELD(arg0, s16, 0x38) != 0) {
        return;
    }
    if (FIELD(arg0, s16, 0x3C) != 0) {
        return;
    }
    temp_v0_3 = D_80028220[9] + 1;
    D_80028220[9] = temp_v0_3;
    if ((u32)(temp_v0_3 & 0xFF) >= 0x20U) {
        D_80028220[9] = 0;
    }
}
