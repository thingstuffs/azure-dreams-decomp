#include "common.h"

extern s32 func_80019DFC(void *, void *, s32, s32);
extern u8 D_8001B910[];
extern u8 D_8001C354[];

/* Return the dispatch result for the fixed data tables and first and third arguments. */
s32 func_80016874(s32 dispatch_value, s32 unused, s32 dispatch_option)
{
    return func_80019DFC(D_8001B910, D_8001C354, dispatch_value, dispatch_option);
}
