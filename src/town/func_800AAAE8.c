#include "common.h"

extern s32 D_800834B8[2];
extern s32 D_80097D2C;
extern s32 D_80097EA0;
extern s32 D_800814A0[3];
extern s32 D_80083780[3];
extern s32 D_800D0428;

extern void func_80033D08(void *arg0);

void func_800A8248(void *arg0, s32 *arg1)
{
    s32 *state = D_800834B8;

    if ((state[0] != (s32)&D_80097D2C) ||
        (state[1] != (s32)&D_80097EA0)) {
        func_80033D08(arg0);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    arg1[0] = D_80083780[0];
    arg1[1] = D_80083780[1];
    arg1[2] = D_80083780[2] + D_800D0428;
}
