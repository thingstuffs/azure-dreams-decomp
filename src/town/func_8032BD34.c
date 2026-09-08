#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
#ifndef NON_MATCHING
#else
#endif
extern void func_80019958(s32 arg0, s32 arg1);

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
register s32 dispatch_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
#endif

s32 func_80016534(s32 arg0, s32 arg1) {
#ifndef NON_MATCHING
    if (func_8001ADE0(0x1463) == 0) {
        dispatch_arg = arg0;
        __asm__ __volatile__("" : "=r"(dispatch_arg) : "0"(dispatch_arg));
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result = 0;
        return;
    }
#else
    if (func_8001ADE0(0x1463) == 0) {
        return;
    }
#endif
    func_80019958(arg0, arg1);
    return 1;
}
