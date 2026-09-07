#include "common.h"

extern void func_80019DFC(void *, void *, s32, s32);
extern s32 D_8001B920;
extern u8 D_8001B924[];
extern u8 D_8001B944[];
extern s32 D_8001C354;

void func_8001698C(s32 arg0, s32 arg1, s32 arg2) {
    void *arg_ptr;

    if (D_8001B920 != 0) {
        arg_ptr = D_8001B944;
    } else {
        arg_ptr = D_8001B924;
    }
    if (arg2 != 0x2D) {
        D_8001B920 = 1;
    }
    func_80019DFC(arg_ptr, &D_8001C354, arg0, arg2);
}
