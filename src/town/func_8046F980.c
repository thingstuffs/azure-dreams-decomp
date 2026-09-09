#include "common.h"

extern s32 func_80019928(void);
extern void func_8001A418(s32);
extern void func_8001A490(s32);

s32 func_80016980(void) {
    s32 result;

    result = func_80019928();
    if (result == 0) {
        func_8001A418(0x7A0);
    } else {
        func_8001A490(0x7A0);
    }
    return result;
}
