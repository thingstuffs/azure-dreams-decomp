#include "common.h"

void func_8008C1C4(s32 arg0, s32 arg1, s32 arg2, u8 *arg3)
{
    s32 hi;
    s32 value;

    hi = arg1 % arg2;
    arg0 &= 0xF;
    arg3 += hi / 2;

    if (!(hi & 1)) {
        value = (*arg3 & 0xF0) | arg0;
    } else {
        value = (*arg3 & 0xF) | (arg0 << 4);
    }

    *arg3 = value;
}
