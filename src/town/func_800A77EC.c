#include "common.h"

extern u32 func_800352FC(void *, s32, s32, s32);
extern void func_800A4F84(void);

void func_800A4F4C(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_800352FC(arg0, arg1, arg2, arg3) != 0) {
        *(void **)((u8 *)arg0 + 0x24) = func_800A4F84;
    }
}
