#include "common.h"

typedef struct {
    u8 pad[0xA8];
    u8 unkA8;
    u8 unkA9;
    u8 unkAA;
} DungeonState;

extern DungeonState D_80083160;
extern s32 D_800814A0[];
extern void func_8016AC28(void) __attribute__((noreturn));

s32 func_8016ABC8(u16 *arg0)
{
    u32 value = D_80083160.unkA8;

    ASM_KEEP(value);

    if ((value & 0xFF) < 0x80U) {
        D_80083160.unkA8 = value + 4;
        D_80083160.unkA9 += 4;
        D_80083160.unkAA += 4;
        func_8016AC28();
    }

    arg0[-1] |= 0x8000;
    return D_800814A0[0] |= 0x8000;
}
