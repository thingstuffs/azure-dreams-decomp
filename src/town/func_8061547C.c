#include "common.h"

extern s32 func_800181C8(void *, void *, s32, s32);
extern u8 D_80018F9C[];
extern u8 D_8001925C[];

/* Invoke func_800181C8 with D_80018F9C and the shared D_8001925C table. */
s32 func_80016C7C(s32 request, s32 unused, s32 parameter)
{
    return func_800181C8(D_80018F9C, D_8001925C, request, parameter);
}
