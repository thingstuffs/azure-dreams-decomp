#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001B918[];
extern u8 D_8001C354[];

/* Process the request using D_8001B918 and D_8001C354. */
s32 func_80016900(s32 request, s32 unused, s32 context)
{
    return func_80019DFC(D_8001B918, D_8001C354, request, context);
}
