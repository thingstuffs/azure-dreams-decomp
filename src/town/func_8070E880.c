#include "common.h"

__asm__(".set jtbl_800164F0, 0x800164F0");
extern void *jtbl_800164F0[43];

extern char D_8001B14C[];
extern char D_8001BF7C[];
extern char D_8001C6D0[];
extern char D_8001C8AF[];
extern char D_8001C8DC[];
extern char D_80021EE4[];

extern char *func_80016E48(s32);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);

char *func_80017880(s32 arg0, s32 arg1, s32 arg2)
{
    s32 selector = arg2;
    u32 index;
    static void *const keepalive[] = {
        &&L_case12,
        &&L_case18,
        &&L_case19,
        &&L_case52,
        &&L_default
    };

    index = selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    
    goto *jtbl_800164F0[index];

L_case19:
    return D_8001BF7C;

L_case18:
    return D_80021EE4;

L_case52:
    return func_80016E48(selector);

L_case12:
    func_8001A554(0x943);
    if (func_8001A64C(0x935) != 0) {
        return D_8001C8AF;
    }
    if (func_8001A64C(0x936) != 0) {
        return D_8001C8DC;
    }
    return D_8001C6D0;

L_default:
    return D_8001B14C;
}
