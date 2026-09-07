#include "common.h"

extern void *jtbl_80024008[];
extern void func_80024CFC(void);
extern void func_80024E44(void);
extern void func_80024EF8(void);
extern void func_80025080(void) __attribute__((noreturn));

__asm__(".set jtbl_80024008, 0x80024008");

s32 func_80025020(void *arg0)
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
    func_80024CFC();
    func_80025080();
L_case1:
    func_80024E44();
    func_80025080();
L_case2:
    func_80024EF8();
L_default:
    return 0;
}
