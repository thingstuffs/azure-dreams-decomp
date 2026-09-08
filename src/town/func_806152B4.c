#include "common.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018F6C[];
extern u8 D_8001925C[];

/* Invoke func_800181C8 with D_80018F6C and the shared D_8001925C table. */
s32 func_80016AB4(s32 request, s32 unused, s32 parameter)
{
    return func_800181C8(D_80018F6C, D_8001925C, request, parameter);
}
