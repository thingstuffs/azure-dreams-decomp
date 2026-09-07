#include "common.h"

s32 func_800A35D8(s32 arg0, s32 arg1) {
    register s32 result ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 flags0 ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 flags1 ASM_REG("$6");   /* MATCH pin: retail keeps a computation the compiler would drop */
    register s32 next ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
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
