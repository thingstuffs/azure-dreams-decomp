#include "common.h"

extern void func_80033D08(void *arg0);
extern void func_80098928(void *arg0, s32 arg1, s32 arg2);
extern u8 D_80082660;

void func_8009A494(void *arg0, s32 arg1, s32 arg2) {
    func_80033D08(arg0);
    *(((*(s32 *)((u8 *)arg0 + 0x40)) * 8) + &D_80082660) = 0;
    func_80098928(arg0, arg1, arg2);
}
