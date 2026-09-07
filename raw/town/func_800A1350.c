#include "common.h"

extern s32 func_8009EB9C(s32 arg0, void *arg1, s32 arg2, s32 arg3, void *arg4);
extern void func_8009BFD8(s32 arg0, void *arg1, s32 arg2, s32 arg3);

void func_8009EAB0(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 sp18[6];

    *((s8 *)arg1 + 0x15) = 0;
    if (func_8009EB9C(arg0, arg1, arg2, arg3, sp18) == 0) {
        func_8009BFD8(arg0, arg1, arg2, arg3);
    }
}
