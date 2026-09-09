#include "common.h"

extern void *jtbl_80024008[];
extern s32 func_80024CFC(void *, s32, s32);
extern s32 func_80024E44(void *, s32, s32);
extern s32 func_80024EF8(void *, s32, s32);

__asm__(".set jtbl_80024008, 0x80024008");

/* Dispatch effect rendering by effect type. */
s32 func_80025020(void *effect, s32 position, s32 render_param)
{
    s32 dispatch_index;
    void **dispatch_table;
    void *handler;
    static void *const case_labels[] = {
        &&L_case0,
        &&L_case1,
        &&L_case2,
        &&L_default,
        &&L_default,
        &&L_default,
        &&L_default,
    };

    dispatch_index = *(s16 *)((u8 *)effect + 0xA);
    if ((u32)dispatch_index >= 7) {
        goto L_default;
    }
    dispatch_index <<= 2;
    dispatch_table = jtbl_80024008;
    dispatch_index = (s32)((u8 *)dispatch_table + dispatch_index);
    handler = *(void **)(u32)dispatch_index;
    (void)case_labels;
    goto *handler;

L_case0:
    func_80024CFC(effect, position, render_param);
    goto L_default;
L_case1:
    func_80024E44(effect, position, render_param);
    goto L_default;
L_case2:
    func_80024EF8(effect, position, render_param);
L_default:
    return 0;
}
