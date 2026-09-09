#include "common.h"

typedef struct {
    u8 pad[0xA8];
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
} DungeonState;

extern DungeonState D_80083160;
extern s32 D_800814A0[];

/* Increments three state bytes while the first is below 0x80, otherwise sets flag bits. */
s32 func_8016ABC8(u16 *words)
{
    u8 state_value = D_80083160.unkA8;

    if (state_value < 0x80U) {
        D_80083160.unkA8 = state_value + 4;
        D_80083160.unkA9 += 4;
        D_80083160.unkAA += 4;
        return;
    }

    words[-1] |= 0x8000;
    return D_800814A0[0] |= 0x8000;
}
