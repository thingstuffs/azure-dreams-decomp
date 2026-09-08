#include "common.h"

extern s32 func_80016CB0(void *, void *, s32, s32);
extern u8 D_8001775C[];
extern u8 D_80017890[];

/* Passes the value and line to the handler with its fixed data tables. */
s32 func_806CB0C0(s32 value, s32 unused, s32 line)
{
    return func_80016CB0(D_8001775C, D_80017890, value, line);
}
