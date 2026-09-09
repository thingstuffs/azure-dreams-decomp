#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001EB20[];

register s32 dispatch_result ASM_REG("$2");

/* Select one of two data pointers based on the query for 0xD83. */
void *func_80016A84(void) {
    if (func_8001ADE0(0xD83) != 0) {
        dispatch_result = 0x80020000;
        dispatch_result -= 0x1396;
        goto merge;
    }
    ASM_SCHED_BARRIER();
    dispatch_result = 0x80020000;
    dispatch_result -= 0x14E0;
merge:
    __asm__ __volatile__("" ::: "memory");
    return (void *)dispatch_result;
}
