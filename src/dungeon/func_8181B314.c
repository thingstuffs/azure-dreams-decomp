#include "common.h"

extern s16 D_80025914[5];
extern s32 D_800814A0[3];

void func_8181B314(void *arg0, s32 arg1, void *arg2) {
    u16 counter;
    u8 *state = arg0;

    counter = *(u16 *)(state + 2) + 2;
    D_80025914[0] = 1;
    *(u16 *)(state + 2) = counter;
    if ((s16)counter < 40) {
        *(s16 *)((u8 *)arg2 + 0x1C) = (s16)counter * 204;
        *(s16 *)((u8 *)arg2 + 0x1E) =
            (s16)*(u16 *)(state + 2) * 204;
    }
    if ((s16)*(u16 *)(state + 2) >= 120) {
        *(u16 *)(state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x8000) {
        *(u16 *)(state - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
