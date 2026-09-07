#include "common.h"

extern s16 D_800269B4;
extern s32 D_800814A0;

void func_8196B25C(void *arg0, s32 arg1, u8 *arg2) {
    u16 value = *(u16 *)((u8 *)arg0 + 0x2C);

    D_800269B4 = 1;
    value -= 1;
    *(u16 *)((u8 *)arg0 + 0x2C) = value;

    if (arg2[12] >= 65) {
        arg2[14] = 64;
        arg2[13] = 64;
        arg2[12] = 64;
    }

    if (arg2[12] != 0) {
        s32 temp = arg2[14] - 5;

        arg2[14] = temp;
        arg2[13] = temp;
        arg2[12] = temp;
    }

    if (*(s16 *)((u8 *)arg0 + 0x2C) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
