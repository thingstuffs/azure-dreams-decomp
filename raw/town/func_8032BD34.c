#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
#ifndef NON_MATCHING
extern void func_80016570(void) __attribute__((noreturn));
#else
extern void func_80016570(s32 arg0) __attribute__((noreturn));
#endif
extern void func_80019958(s32 arg0, s32 arg1);

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");
register s32 dispatch_arg ASM_REG("$4");
#endif

s32 func_80016534(s32 arg0, s32 arg1) {
#ifndef NON_MATCHING
    if (func_8001ADE0(0x1463) == 0) {
        dispatch_arg = arg0;
        __asm__ __volatile__("" : "=r"(dispatch_arg) : "0"(dispatch_arg));
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result = 0;
        func_80016570();
    }
#else
    if (func_8001ADE0(0x1463) == 0) {
        func_80016570(arg0);
    }
#endif
    func_80019958(arg0, arg1);
    return 1;
}
