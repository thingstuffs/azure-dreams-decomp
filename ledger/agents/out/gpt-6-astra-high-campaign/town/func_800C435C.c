#include "common.h"

extern s32 D_8006ADD4[];
extern u8 D_80083160[];

/* Set the state halfword at offset 0xC4 to -0x240 when D_8006ADD4[0] is 0x3E000C. */
void func_800C1ABC(void) {
    u8 *state = D_80083160;

    if (D_8006ADD4[0] == 0x3E000C) {
        *(s16 *)(state + 0xC4) = -0x240;
    }
}
