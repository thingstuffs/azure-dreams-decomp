#include "common.h"

extern void func_8004437C(s16, s32);
extern void func_80053DA8(s32);

s32 func_800C1564(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        func_8004437C(arg0, 0);
    }
    if (arg1 != 0) {
        func_80053DA8((arg1 | arg2) & 0xFFFF);
    }
    return 1;
}
