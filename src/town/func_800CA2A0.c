#include "common.h"

extern s32 func_800C30E0(s32, s32, s32, s32);
extern void func_800C7BF0(s32, s32, s32);
extern s32 D_80113220[];

void func_800C7A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_800C30E0(arg0, arg1, arg2, arg3) == 0) {
        if (--D_80113220[0] <= 0) {
            func_800C7BF0(arg0, arg1, arg2);
        }
    }
}
