#include "common.h"

extern char D_8001B14C[];
extern char D_8001BA48[];
extern char D_8001C6D0[];
extern char D_800213D4[];

extern char *func_80016E48(s32);
extern void func_8001A554(s32);

/* Selects a string and performs any associated action. */
char *func_8001769C(s32 unused_0, s32 unused_1, s32 selector)
{

    switch (selector - 12) {
    case 7:
        func_8001A554(0x932);
        return D_8001BA48;
    case 6:
        return D_800213D4;
    case 40:
    case 41:
    case 42:
        return func_80016E48(selector);
    case 0:
        return D_8001C6D0;
    default:
        return D_8001B14C;
    }
}
