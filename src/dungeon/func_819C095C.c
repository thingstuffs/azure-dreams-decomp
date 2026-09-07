#include "common.h"

extern void func_800478B8(void *arg0);
extern s16 D_8002992E[5];
extern s32 D_800814A0;

void func_8002615C(void *arg0, void *arg1, void *arg2) {
    s32 temp_a0;
    s32 temp_a1;
    u16 temp_v0;
    u16 temp_v0_2;

    *(s32 *)((u8 *)arg1 + 0) += *(s32 *)((u8 *)arg0 + 0x7C);
    *(s32 *)((u8 *)arg1 + 4) += *(s32 *)((u8 *)arg0 + 0x80);
    *(s32 *)((u8 *)arg1 + 8) += *(s32 *)((u8 *)arg0 + 0x84);
    temp_a0 = *(s32 *)((u8 *)arg0 + 0x8C);
    temp_a1 = *(s32 *)((u8 *)arg0 + 0x90);
    *(s32 *)((u8 *)arg0 + 0x7C) += *(s32 *)((u8 *)arg0 + 0x88);
    *(s32 *)((u8 *)arg0 + 0x80) += temp_a0;
    *(s32 *)((u8 *)arg0 + 0x84) += temp_a1;
    *(u16 *)((u8 *)arg2 + 0x1C) -= 500;
    *(u16 *)((u8 *)arg2 + 0x1E) -= 500;
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x2A);
    D_8002992E[0] = 1;
    temp_v0 += 1;
    *(u16 *)((u8 *)arg0 + 0x2A) = temp_v0;
    if (!(temp_v0 & 1)) {
        func_800478B8(arg2);
    }
    temp_v0_2 = *(u16 *)((u8 *)arg0 + 0x28) - 1;
    *(u16 *)((u8 *)arg0 + 0x28) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
