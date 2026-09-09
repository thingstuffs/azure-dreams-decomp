#include "common.h"

extern s32 func_80065F90();

s32 func_800A0818(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 *arg4) {
    s32 temp_v0;
    u16 val;

    {
        s32 test_result;
        test_result = func_80065F90(arg3 - arg1, arg2 - arg0, arg2, arg3);
        temp_v0 = test_result;
        ASM_KEEP_NV(test_result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if ((test_result & 0x1FF) < 0x100) {
            goto in_range;
        }
    }
    val = *arg4 | 2;
    goto store;
in_range:
    val = *arg4 & 0xFFFD;
store:
    *arg4 = val;
    return (temp_v0 + 0x100) & 0xE00;
}
