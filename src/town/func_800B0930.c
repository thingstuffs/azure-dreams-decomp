#include "common.h"

extern void func_800ADB30(void *arg0);
extern s32 D_800ADD80[4];

#ifndef NON_MATCHING
register u8 *dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

void func_800AE090(void *arg0) {
    u8 *p = (u8 *)arg0;

#ifndef NON_MATCHING
    register s32 value_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    __asm__ __volatile__("" : "=r"(p) : "0"(p));
    value_v0 = *(s32 *)(p + 0x14);
    value_v0--;
    *(s32 *)(p + 0x14) = value_v0;
    if (value_v0 == 0) {
        value_v0 = *(s32 *)(p + 0x1C);
        if (value_v0 != 0) {
            dispatch_result = (u8 *)0x800B0000;
            dispatch_result -= 0x24A4;
        } else {
            dispatch_result = (u8 *)0x800B0000;
            func_800ADB30(p);
            dispatch_result = (u8 *)D_800ADD80;
        }
        *(u8 **)(p - 0x10) = dispatch_result;
    }
#else
    if (--*(s32 *)(p + 0x14) == 0) {
        if (*(s32 *)(p + 0x1C) != 0) {
            /* tail falls through */
        }
        func_800ADB30(p);
        *(void **)(p - 0x10) = D_800ADD80;
    }
#endif
}
