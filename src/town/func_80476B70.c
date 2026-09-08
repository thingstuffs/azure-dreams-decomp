#include "common.h"

extern s32 func_80018FC8(void *, void *, s32, s32);
extern u8 D_800165E0[];
extern u8 D_800170CC[];

/* Forward the request and option values with the D_800165E0 and D_800170CC tables. */
s32 func_80017B70(s32 request_value, s32 unused, s32 option_value)
{
    return func_80018FC8(D_800165E0, D_800170CC, request_value, option_value);
}
