#include "common.h"

extern s32 func_80019AB8(s32, s32);
extern void func_80019BC0(void);
extern s32 func_80019B54(s32, s32);
extern void func_8001AD60(s32);

/* Processes the selected context entry and applies a fallback value on failure. */
s32 func_800184B8(s32 entryContext, s32 entryIndex)
{
    if (func_80019AB8(13, 1) != 0) {
        func_80019BC0();
    }

    if (func_80019B54(entryContext, entryIndex) == 0) {
        func_8001AD60(0xD7F);
        return 0;
    }

    return 1;
}
