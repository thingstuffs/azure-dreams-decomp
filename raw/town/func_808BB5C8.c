#include "common.h"

extern s32 D_00000FD0[];
extern s32 D_00001038;

void func_808BB5C8(void) {
    D_00000FD0[0] = (D_00000FD0[0] * 8) + D_00001038;
}
