#include "common.h"

extern void *D_80016390[43];

extern char D_8001B14C[];
extern char D_8001BA48[];
extern char D_8001C6D0[];
extern char D_800213D4[];

extern char *func_80016E48(s32);
extern void func_8001A554(s32);

char *func_8001769C(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 selector ASM_REG("$4") = arg2;
    u32 index;
    static void *const keepalive[] = {
        &&L_case19, &&L_case18, &&L_case52, &&L_case12, &&L_default
    };

    index = selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    ASM_KEEP(selector);
    goto *D_80016390[index];

L_case19:
    func_8001A554(0x932);
    return D_8001BA48;

L_case18:
    return D_800213D4;

L_case52:
    return func_80016E48(selector);

L_case12:
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
