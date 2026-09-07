#include "common.h"

typedef struct {
    u8 pad[0xA8];
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
} DungeonState;

extern DungeonState D_80083160;
extern s32 D_800814A0[];

s32 func_80170230(u16 *arg0)
{
    u32 value = D_80083160.unkA8;

    ASM_KEEP(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if ((value & 0xFF) < 0x80U) {
        D_80083160.unkA8 = value + 2;
        D_80083160.unkA9 += 2;
        D_80083160.unkAA += 2;
        return;
    }

    arg0[-1] |= 0x8000;
    return D_800814A0[0] |= 0x8000;
}
