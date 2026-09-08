#include "common.h"

typedef struct {
    u8 pad[0xA8];
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
} DungeonState;

extern DungeonState D_80083160;
extern s32 D_800814A0[];

/* Increment three dungeon state bytes by two, or set flags when the first reaches 0x80. */
s32 func_80170230(u16 *dataCursor)
{
    u32 firstStateByte = D_80083160.unkA8;

    ASM_KEEP(firstStateByte);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if ((firstStateByte & 0xFF) < 0x80U) {
        D_80083160.unkA8 = firstStateByte + 2;
        D_80083160.unkA9 += 2;
        D_80083160.unkAA += 2;
        return;
    }

    dataCursor[-1] |= 0x8000;
    return D_800814A0[0] |= 0x8000;
}
