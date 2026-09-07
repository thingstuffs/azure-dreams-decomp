#include "common.h"

extern void *D_800162E0[43];

extern char D_8001B14C[];
extern char D_8001B9E8[];
extern char D_8001C6D0[];
extern char D_80021386[];

extern char *func_80016E48(void);

char *func_80017580(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 selector ASM_REG("$4") = arg2;   /* MATCH pin: retail delay-slot fill depends on it */
    u32 index;
    static void *const keepalive[] = {
        &&L_case19, &&L_case18, &&L_case52, &&L_case12, &&L_default
    };

    index = selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    ASM_KEEP(selector);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    goto *D_800162E0[index];

L_case19:
    return D_8001B9E8;

L_case18:
    return D_80021386;

L_case52:
    return func_80016E48();

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
