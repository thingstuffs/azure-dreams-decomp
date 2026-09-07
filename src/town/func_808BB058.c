#include "common.h"

extern u8 D_00000F48[];
extern void func_80000BC8(s32);

__asm__(".set D_00000F48, 0xF48");

void func_808BB058(s32 arg0, s32 arg1) {
    s32 offset;

    offset = (arg1 * 8) + (arg0 << 4);
    if (*(s32 *)&D_00000F48[offset] & 1) {
        func_80000BC8(0x278);
    }
}
