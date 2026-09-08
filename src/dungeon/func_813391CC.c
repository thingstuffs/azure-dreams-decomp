#include "common.h"

extern s8 D_80083160[];
extern s32 D_800814A0[];

/* Decrease three state bytes, or set entry and global flags below the threshold. */
void func_801701CC(u16 *entry)
{
    u8 *state = D_80083160;

    if (state[0xA8] >= 0x3D) {
        state[0xA8] -= 2;
        state[0xA9] -= 2;
        state[0xAA] -= 2;
        return;
    }

    entry[-1] |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
