#include "common.h"

extern void func_80022C48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_800226E0(s32 arg0, s32 arg1, s32 arg2);
extern void func_80022AE8(s32 arg0);

void func_80022C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_80022C48(arg0, arg1, arg2, arg3, arg4);
    func_800226E0(arg0 + 0x8BC, arg0 + 0x894, arg0 + 0x8A4);
    func_80022AE8(arg0);
}
