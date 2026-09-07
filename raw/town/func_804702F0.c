#include "common.h"

extern void func_80019618(s32, s32);
extern s32 func_80019928(s32, s32);
extern s32 func_8001A510(s32);
extern s32 D_8001B208;

s32 func_800172F0(s32 arg0, s32 arg1) {
    s32 result;

    if (func_8001A510(0x799) != 0) {
        D_8001B208 = 0;
        result = func_80019928(arg0, arg1);
    } else {
        func_80019618(arg0, arg1);
        result = 1;
    }
    return result;
}
