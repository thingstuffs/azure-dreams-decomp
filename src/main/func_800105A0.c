#include "common.h"

extern void func_80049D80(s32 arg0, s16 *arr);

s32 func_800235A0(s32 arg0, s32 arg1, s32 arg2) {
    s16 sp10[4];

    sp10[0] = (s16) (-arg1 / 2);
    sp10[2] = (s16) arg1;
    sp10[1] = (s16) (-arg2 / 2);
    sp10[3] = (s16) arg2;
    func_80049D80(arg0, sp10);
    return arg0;
}
