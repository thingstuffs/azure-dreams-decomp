#include "common.h"

extern void func_80098834(s32 arg0, s32 arg1, s32 arg2);
extern void func_80098928(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_80093D48;
extern s32 *D_800FE5D8;

void func_80098868(s32 arg0, s32 arg1, s32 arg2) {
    func_80098834(arg0, arg1, arg2);
    func_80098928(arg0, arg1, arg2);
    D_800FE5D8 = &D_80093D48;
}
