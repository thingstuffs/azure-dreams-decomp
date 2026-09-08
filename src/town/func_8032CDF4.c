#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001BB64[];
extern u8 D_8001C354[];

/* Dispatch through D_8001BB64 and D_8001C354 and return the result. */
s32 func_800175F4(s32 dispatch_value, s32 unused, s32 dispatch_context)
{
    return func_80019DFC(D_8001BB64, D_8001C354, dispatch_value, dispatch_context);
}
