#include "common.h"

extern u8 *func_80019DFC();
extern s32 func_8001ADE0(s32);
extern s32 D_8001BB6C;
extern s32 D_8001C354;

register u8 *dispatch_result ASM_REG("$2");

u8 *func_80017694(s32 arg0, s32 arg1, s32 arg2) {
    u8 *result;
    register s32 first_arg ASM_REG("$2") = arg0;
    register s32 fourth_arg ASM_REG("$7") = arg2;

    __asm__("" : "=r"(fourth_arg) : "0"(fourth_arg));

    result = func_80019DFC(&D_8001BB6C, &D_8001C354, first_arg, fourth_arg);
    if (func_8001ADE0(0x1390) != 0) {
        dispatch_result = (u8 *)0x80020000;
        dispatch_result -= 0x74B;
        return dispatch_result;
    }
    dispatch_result = (u8 *)0x80020000;
    dispatch_result = result;
    return dispatch_result;
}
