#include "common.h"

extern u32 func_80019C68(void);
extern void func_80017F74(void) __attribute__((noreturn));
extern void func_8001AD60(s32 arg0);
extern u8 D_8001F15A[];

s32 func_80017F3C(void) {
    register s32 result ASM_REG("$16");

    result = func_80019C68();
    if (result == 0)
        goto zero_result;
    D_8001F15A[0] = 0;
    func_80017F74();
zero_result:
    ASM_SCHED_BARRIER();
    D_8001F15A[0] = 1;
    func_8001AD60(0xD7A);
    return result;
}
