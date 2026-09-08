#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
#ifndef NON_MATCHING
#else
#endif
extern void func_80019958(s32 arg0, s32 arg1);

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
register s32 dispatch_arg ASM_REG("$4");   /* MATCH pin: retail basic-block layout depends on it */
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
