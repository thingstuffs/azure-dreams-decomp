#include "common.h"

extern s32 func_80016A2C(void *, void *, s32, s32);
extern u8 D_800173B4[];
extern u8 D_80017474[];

/* Passes the value and line to the handler with its fixed data tables. */
s32 func_806D10C0(s32 value, s32 unused, s32 line)
{
    return func_80016A2C(D_800173B4, D_80017474, value, line);
}
