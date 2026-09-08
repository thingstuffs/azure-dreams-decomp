#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800165F8[];
extern u8 D_800170D0[];

/* Forward the request and option values with the D_800165F8 and D_800170D0 tables. */
s32 func_80017BA8(s32 request_value, s32 unused, s32 option_value)
{
    return func_80018FC8(D_800165F8, D_800170D0, request_value, option_value);
}
