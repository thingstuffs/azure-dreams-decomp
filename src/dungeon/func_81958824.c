#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80065820(s32, s32 *);
extern void func_8003E0C4(s32 *, s32 *, M2C_UNK);

void func_81958824(s32 arg0, s32 arg1, M2C_UNK arg2) {
    s32 sp10[10];

    sp10[7] = 0;
    sp10[6] = 0;
    sp10[5] = 0;
    sp10[8] = 0;
    sp10[9] = arg1 << 0xC;
    func_80065820(arg0, sp10);
    func_8003E0C4(sp10, &sp10[8], arg2);
}
