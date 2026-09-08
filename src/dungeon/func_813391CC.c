#include "common.h"

extern s8 D_80083160[];
extern s32 D_800814A0[];

void func_801701CC(u16 *arg0)
{
    u8 *p = D_80083160;

    if (p[0xA8] >= 0x3D) {
        p[0xA8] -= 2;
        p[0xA9] -= 2;
        p[0xAA] -= 2;
        return;
    }

    arg0[-1] |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
