#include "common.h"

extern s32 func_8009CFE0(void);
extern void func_80033D08(void *arg0);
extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];

void func_800A7B14(void *arg0, void *arg1, void *arg2)
{
    u8 *p;

    if (func_8009CFE0() != 0) {
        p = *(u8 **)((u8 *)arg0 + 0x98);
        if (p != 0) {
            *p = 0;
        }
        func_80033D08(arg0);
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    } else {
        func_800478B8(arg2);
    }
}
