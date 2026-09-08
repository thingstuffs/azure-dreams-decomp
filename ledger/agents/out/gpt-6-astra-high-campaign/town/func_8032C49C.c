#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001BA2C[];
extern u8 D_8001C354[];

/* Process the request using D_8001BA2C and D_8001C354. */
s32 func_80016C9C(s32 request, s32 unused, s32 context)
{
    return func_80019DFC(D_8001BA2C, D_8001C354, request, context);
}
