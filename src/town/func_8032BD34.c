#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern void func_80019958(s32 arg0, s32 arg1);

s32 func_80016534(s32 dispatch_value, s32 dispatch_option) {
    if (func_8001ADE0(0x1463) != 0) {
        func_80019958(dispatch_value, dispatch_option);
        return 1;
    }
    return 0;
}
