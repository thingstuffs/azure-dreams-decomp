#include "common.h"

extern void *jtbl_80024008[];
extern s32 func_80024CFC(void *, s32, s32);
extern s32 func_80024E44(void *, s32, s32);
extern s32 func_80024EF8(void *, s32, s32);

__asm__(".set jtbl_80024008, 0x80024008");

s32 func_80025020(void *arg0, s32 arg1, s32 arg2)
{
    s32 index;
    void **table;
    void *target;
    static void *const keepalive[] = {
        &&L_case0,
        &&L_case1,
        &&L_case2,
        &&L_default,
        &&L_default,
        &&L_default,
        &&L_default,
    };

    index = *(s16 *)((u8 *)arg0 + 0xA);
    if ((u32)index >= 7) {
        goto L_default;
    }
    index <<= 2;
    table = jtbl_80024008;
    index = (s32)((u8 *)table + index);
    target = *(void **)(u32)index;
    (void)keepalive;
    goto *target;

L_case0:
    func_80024CFC(arg0, arg1, arg2);
    goto L_default;
L_case1:
    func_80024E44(arg0, arg1, arg2);
    goto L_default;
L_case2:
    func_80024EF8(arg0, arg1, arg2);
L_default:
    return 0;
}
