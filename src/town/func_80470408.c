#include "common.h"

extern void func_80019618(s32, s32);
extern void func_80019928(s32, s32);
extern void func_8001A490(s32);
extern s32 func_8001A510(s32);

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#endif

s32 func_80017408(s32 arg0, s32 arg1) {
#ifndef NON_MATCHING
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_8001A490(0x11FB);
        func_80019618(arg0, arg1);
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        dispatch_result = 1;
        return 1;
    }
    func_80019928(arg0, arg1);
#else
    if ((func_8001A510(0x798) != 0) || (func_8001A510(0x799) != 0)) {
        func_8001A490(0x11FB);
        func_80019618(arg0, arg1);
        return 1;
    }
    func_80019928(arg0, arg1);
    return 0;
#endif
}
