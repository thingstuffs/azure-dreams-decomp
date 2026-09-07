#include "common.h"

extern void func_800AEEBC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_800AEBC4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_800AECA4(s32 arg0);

void func_800AEEF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800AEEBC(arg0, arg1, arg2, arg3, arg6);
    func_800AEBC4(arg0, arg0 + 0xC8, arg0 + 0xA0, arg0 + 0xB0, arg4, arg5);
    func_800AECA4(arg0);
}
