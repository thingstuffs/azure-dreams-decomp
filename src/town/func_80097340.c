#include "common.h"

s32 func_80094AA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 adjusted;
    s32 original;
    s32 scratch;

    arg0 &= 0xFFF;
    arg1 &= 0xFFF;
    if (arg0 == arg1) {
        goto return_arg1;
    }

    original = arg0;
    adjusted = original + 0x1000;
    arg0 = adjusted - arg1;
    arg0 &= 0xFFF;
    if (arg0 < 0x800) {
        arg0 -= arg2;
        if (arg0 >= 0) {
            scratch = original - arg2;
            ASM_KEEP(scratch);   /* MATCH pin: retail delay-slot contents depend on it */
            return;
        }
    } else {
        arg0 += arg2;
        if (arg0 < 0x1001) {
            return original + arg2;
        }
    }
return_arg1:
       /* MATCH pin: retail basic-block layout depends on it */
    return arg1;
}
