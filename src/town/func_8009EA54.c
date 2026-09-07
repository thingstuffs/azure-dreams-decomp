#include "common.h"

extern s32 func_8009B120(void *arg0);
extern void func_8004437C(s32 a0, s32 a1);
extern short func_80053DA8(int a0);
extern u8 D_8009B9BC[];

void func_8009C1B4(u8 *arg0, s8 *arg1, s32 *arg2)
{
    arg1[0x15] = 0;
    arg2[3] = 0;
    arg2[4] = 0;
    arg2[5] = 0;
    *(void **)(arg0 + 0x50) = D_8009B9BC;
    if (func_8009B120(arg0 + 0x4C) != 0) {
        func_8004437C(0x26, 0);
        func_80053DA8(0x200);
    }
}
