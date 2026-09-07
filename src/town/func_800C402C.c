#include "common.h"

extern s16 D_800D4258[2];
__asm__(".set D_800D4258, 0x800D4258");

void func_800C178C(s16 arg0, s16 arg1) {
    D_800D4258[0] = arg0;
    D_800D4258[1] = arg1;
}
