#include "common.h"

extern s32 D_8006ADD4[];
extern u8 D_80083160[];

void func_800C1ABC(void) {
    u8 *base = D_80083160;

    if (D_8006ADD4[0] == 0x3E000C) {
        *(s16 *)(base + 0xC4) = -0x240;
    }
}
