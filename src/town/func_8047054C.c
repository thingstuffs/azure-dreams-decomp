#include "common.h"

extern void func_8001759C(void) __attribute__((noreturn));
extern void func_80019618(s32, s32);
extern void func_80019928(s32, s32);
extern s32 func_8001A510(s32);

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
#endif

void func_8001754C(s32 arg0, s32 arg1) {
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_80019618(arg0, arg1);
#ifndef NON_MATCHING
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result = 1;
#endif
        func_8001759C();
    }
    func_80019928(arg0, arg1);
}
