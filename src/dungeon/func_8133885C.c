#include "common.h"

extern u16 D_80016000[8];
extern void func_80041344(void *arg0, s32 arg1);

void func_8016F85C(s32 arg0)
{
    if (arg0 == 1) {
        D_80016000[4] += 0x40;
    }
    func_80041344(D_80016000, 0);
}
