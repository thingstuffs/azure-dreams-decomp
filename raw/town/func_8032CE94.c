#include "common.h"

extern void func_800176E0(void) __attribute__((noreturn));
extern u8 *func_80019DFC();
extern s32 func_8001ADE0(s32);
extern s32 D_8001BB6C;
extern s32 D_8001C354;

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");
#endif

u8 *func_80017694(s32 arg0, s32 arg1, s32 arg2) {
    u8 *result;
    register s32 first_arg ASM_REG("$2") = arg0;
    register s32 fourth_arg ASM_REG("$7") = arg2;

#ifndef NON_MATCHING
    __asm__("" : "=r"(fourth_arg) : "0"(fourth_arg));
#endif

    result = func_80019DFC(&D_8001BB6C, &D_8001C354, first_arg, fourth_arg);
    if (func_8001ADE0(0x1390) == 0) {
#ifndef NON_MATCHING
        dispatch_result = (u8 *)0x80020000;
        dispatch_result = result;
#endif
        func_800176E0();
    }
#ifndef NON_MATCHING
    dispatch_result = (u8 *)0x80020000;
    dispatch_result -= 0x74B;
    return dispatch_result;
#else
    return (u8 *)0x8001F8B5;
#endif
}
