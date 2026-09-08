#include "common.h"

s32 func_800A35D8(s32 arg0, s32 arg1) {
    register s32 result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 flags0 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 flags1 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register s32 next ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp;

    result = 0;
    flags0 = arg0;
    flags1 = arg1;
    arg0 &= 1;
    if (arg0) {
        temp = arg1 & 4;
        arg0 = temp != 0;
        result = arg0;
        temp = arg1 & 2;
        if (temp) {
            result = arg0 - 1;
        }
    }
    temp = flags0 & 2;
    if (temp) {
        temp = flags1 & 1;
        if (temp) {
            result++;
        }
        temp = flags1 & 4;
        if (temp) {
            result--;
        }
    }
    next = flags0 & 4;
    if (!next) {
        return (s16)result;
    }
    temp = flags1 & 2;
    if (temp) {
        result++;
    }
    temp = flags1 & 1;
    if (temp) {
        result--;
    }
    return (s16)result;
}

/* MECHANISM: Frameless leaf; guarded roles hold result/flags in $v1/$a3/$a2.
   A separate $v0 next-mask plus an explicit early return preserves the split CFG
   and both retail sign-extension sites, including the false-edge delay slot. */
