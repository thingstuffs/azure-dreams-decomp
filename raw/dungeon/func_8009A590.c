#include "common.h"

s16 func_8009FCF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg2 &= 0xFF;
    arg0 &= 0xFF;
    arg2 -= arg0;
    if (arg2 < 0) {
        arg2 = -arg2;
    }
    arg3 &= 0xFF;
    arg1 &= 0xFF;
    arg3 -= arg1;
    if (arg3 < 0) {
        arg3 = -arg3;
    }
    ASM_SCHED_BARRIER();
    if (arg2 < arg3) {
        return arg3;
    }
    return arg2;
}
