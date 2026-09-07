#include "common.h"

extern void func_80019DFC(s32 *, s32 *, s32, s32);
extern s32 D_8001B8F8[];
extern s32 D_8001C354[];

void func_800167E8(s32 arg0, s32 arg1, s32 arg2) {
    func_80019DFC(D_8001B8F8, D_8001C354, arg0, arg2);
}
