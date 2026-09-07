#include "common.h"

extern void func_800478B8(void *arg0);
extern s16 D_8002992E[5];
extern s32 D_800814A0[3];

void func_80025088(void *arg0, void *arg1, void *arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 temp_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_3;

    temp_v1_3 = *(u16 *)((u8 *)arg0 + 0x2A);
    D_8002992E[0] = 1;
    temp_v1_3 = temp_v1_3 + 1;
    *(u16 *)((u8 *)arg0 + 0x2A) = temp_v1_3;
    if (!(temp_v1_3 & 1)) {
        func_800478B8(arg2);
    }
    if (*(s16 *)((u8 *)arg0 + 0x2C) == 0) {
        *(u16 *)((u8 *)arg2 + 0x16) = *(u16 *)((u8 *)arg2 + 0x16) + 0x190;
    }
    if (*(s16 *)((u8 *)arg0 + 0x2C) == 1) {
        *(u16 *)((u8 *)arg2 + 0x1A) = *(u16 *)((u8 *)arg2 + 0x1A) + 0x190;
    }
    temp_a0 = *(s32 *)((u8 *)arg0 + 0x7C);
    *(s32 *)((u8 *)arg0 + 0x84) += *(s32 *)((u8 *)arg0 + 0x90);
    if (temp_a0 < 0) {
        temp_a0 += 0xFFFF;
    }
    *(u16 *)((u8 *)arg1 + 2) += temp_a0 >> 16;
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x80);
    if (temp_v1 < 0) {
        temp_v1 += 0xFFFF;
    }
    *(u16 *)((u8 *)arg1 + 6) += temp_v1 >> 16;
    temp_v1_2 = *(s32 *)((u8 *)arg0 + 0x84);
    if (temp_v1_2 < 0) {
        temp_v1_2 += 0xFFFF;
    }
    *(u16 *)((u8 *)arg1 + 0xA) += temp_v1_2 >> 16;
    temp_v0 = *(u16 *)((u8 *)arg2 + 0x14) & 0x8000;
    *(u16 *)((u8 *)arg2 + 0x14) = temp_v0;
    if ((temp_v0 != 0) || (temp_v0_2 = *(u16 *)((u8 *)arg0 + 0x28) - 1,
                            *(u16 *)((u8 *)arg0 + 0x28) = temp_v0_2,
                            ((temp_v0_2 << 16) <= 0))) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
