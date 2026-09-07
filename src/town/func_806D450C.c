#include "common.h"

extern s32 func_8001868C();
extern void func_80018594();
extern s32 func_800177CC();
extern void func_80016FD0();

s32 func_806D450C(void *arg0, s32 arg1) {
    if (func_8001868C(0x145B) != 0) {
        func_80018594(*(s16 *)((u8 *)arg0 + 0x18));
    }
    if (func_800177CC(arg0, arg1) == 0) {
        func_80016FD0();
        return 0;
    }
    return 1;
}
