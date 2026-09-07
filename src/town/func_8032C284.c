#include "common.h"

extern s32 func_8001ADE0(s32 arg0);
extern u8 D_8001EB20[];
extern u8 D_8001EC6A[];

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
#endif

void *func_80016A84(void) {
    if (func_8001ADE0(0xD83) != 0) {
#ifndef NON_MATCHING
        dispatch_result = 0x80020000;
        dispatch_result -= 0x1396;
#else
        (void)D_8001EC6A;
#endif
        return;
    }
    __asm__ __volatile__("" ::: "memory");
#ifndef NON_MATCHING
    dispatch_result = 0x80020000;
    dispatch_result -= 0x14E0;
    return (void *)dispatch_result;
#else
    return D_8001EB20;
#endif
}
