#include "common.h"

extern s32 func_80016CB4(void *, void *, s32, s32);
extern u8 D_80017760[];
extern u8 D_800178C0[];

/* Passes the value and line to the handler with its fixed data tables. */
s32 func_806C90C0(s32 value, s32 unused, s32 line)
{
    return func_80016CB4(D_80017760, D_800178C0, value, line);
}
