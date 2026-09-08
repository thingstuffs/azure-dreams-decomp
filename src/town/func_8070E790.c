#include "common.h"

extern void *D_80016440[43];

extern char D_8001B14C[];
extern char D_8001BCB4[];
extern char D_8001C6D0[];
extern char D_80021484[];

extern char *func_80016E48(void);
extern void func_8001A554(s32);

char *func_80017790(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 selector ASM_REG("$4") = arg2;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u32 index;
    static void *const keepalive[] = {
        &&L_case19, &&L_case18, &&L_case52, &&L_case12, &&L_default
    };

    index = selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    ASM_KEEP(selector);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    goto *D_80016440[index];

L_case19:
    return D_8001BCB4;

L_case18:
    func_8001A554(0x933);
    return D_80021484;

L_case52:
    return func_80016E48();

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
