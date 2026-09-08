#include "common.h"

extern void func_80019618(s32, s32);
extern s32 func_80019928(s32, s32);
extern s32 func_8001A510(s32);
extern s32 D_8001B208;

/* Dispatch the context entry according to flag 0x799 and return its status. */
s32 func_800172F0(s32 context, s32 entryIndex) {
    s32 result;

    if (func_8001A510(0x799) != 0) {
        D_8001B208 = 0;
        result = func_80019928(context, entryIndex);
    } else {
        func_80019618(context, entryIndex);
        result = 1;
    }
    return result;
}
