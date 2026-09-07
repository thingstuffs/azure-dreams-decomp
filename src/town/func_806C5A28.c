#include "common.h"

extern s32 func_800175A8();

void func_80016A28(void) {
    s8 sp10[4];

    sp10[1] = 1;
    sp10[0] = 8;
    sp10[2] = 0;
    sp10[3] = 0;
    func_800175A8(sp10);
}
