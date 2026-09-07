#include "common.h"

extern void func_800ADB30(void *arg0);
extern void func_800AE0DC(void) __attribute__((noreturn));
extern s32 D_800ADD80[4];

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
#endif

void func_800AE090(void *arg0) {
    u8 *p = (u8 *)arg0;

#ifndef NON_MATCHING
    register s32 value_v0 ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */

    __asm__ __volatile__("" : "=r"(p) : "0"(p));
    value_v0 = *(s32 *)(p + 0x14);
    value_v0--;
    *(s32 *)(p + 0x14) = value_v0;
    if (value_v0 == 0) {
        value_v0 = *(s32 *)(p + 0x1C);
        if (value_v0 != 0) {
            dispatch_result = (u8 *)0x800B0000;
            __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
            dispatch_result -= 0x24A4;
            func_800AE0DC();
        }
        dispatch_result = (u8 *)0x800B0000;
        __asm__ __volatile__("" : "=r"(dispatch_result) : "0"(dispatch_result));
        func_800ADB30(p);
        dispatch_result = (u8 *)D_800ADD80;
        *(u8 **)(p - 0x10) = dispatch_result;
    }
#else
    if (--*(s32 *)(p + 0x14) == 0) {
        if (*(s32 *)(p + 0x1C) != 0) {
            func_800AE0DC();
        }
        func_800ADB30(p);
        *(void **)(p - 0x10) = D_800ADD80;
    }
#endif
}
