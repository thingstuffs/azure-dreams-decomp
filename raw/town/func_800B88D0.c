#include "common.h"

extern void func_8004E5A0(void *a0, s32 a1, void *a2);
extern u8 *func_8004E69C(u8 *arg0);

void *func_800B6030(void *arg0, u8 *arg1) {
    u8 *p;

    p = arg1 + 1;
    arg1[0] = 0x20;
    func_8004E5A0(arg0, 2, p);
    arg1[3] = 0xA;
    arg1[4] = 0x6F;
    arg1[5] = 0;
    func_8004E69C(p);
    return arg1;
}
