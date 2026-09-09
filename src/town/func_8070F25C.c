#include "common.h"

extern void *D_80016910[43];

extern char D_8001B14C[];
extern char D_8001C018[];
extern char D_8001D6B5[];
extern char D_8001D7A5[];
extern char D_800227FB[];

extern char *func_80016E48(s32);
extern s32 func_8001A64C(u32);

char *func_8001825C(s32 arg0, s32 arg1, s32 arg2)
{
    register s32 selector ASM_REG("$4") = arg2;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u32 index;
    static void *const keepalive[] = {
        &&L_case19, &&L_case18, &&L_case12, &&L_case52, &&L_default
    };

    index = selector - 12;
    if (index >= 43) {
        goto L_default;
    }
    ASM_KEEP(selector);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    goto *D_80016910[index];

L_case19:
    return D_8001C018;

L_case18:
    return D_800227FB;

L_case12:
    if (func_8001A64C(0x94A) != 0) {
        return D_8001D6B5;
    }
    return D_8001D7A5;

L_case52:
    return func_80016E48(selector);

L_default:
    return D_8001B14C;
}
