#include "common.h"

void func_800B135C(u8 *arg0, s32 arg1) {
    s32 temp_a2 = arg1;
    u8 *arg2;
    arg1 &= 4;
    arg2 = arg0 + 2;

    for (;;) {
        arg0[0] = (u8)(arg0[0] | temp_a2);
        if (arg1 != 0) {
            arg2[0] = (u8)(0 - arg2[0]);
        }
        if ((s8)arg0[0] < 0) {
            return;
        }
        arg2 += 0xc;
        arg0 += 0xc;
    }
}
