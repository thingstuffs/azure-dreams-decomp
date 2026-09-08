#include "common.h"

extern void func_80019DFC(s32 *, s32 *, s32, s32);
extern s32 D_8001B8F8[];
extern s32 D_8001C354[];

/* Dispatch the first and third arguments using the fixed data tables. */
void func_800167E8(s32 dispatch_value, s32 unused, s32 dispatch_option) {
    func_80019DFC(D_8001B8F8, D_8001C354, dispatch_value, dispatch_option);
}
