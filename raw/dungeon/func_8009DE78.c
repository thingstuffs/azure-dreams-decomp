#include "common.h"

s32 func_800A35D8(s32 arg0, s32 arg1) {
    register s32 result ASM_REG("$3");
    register s32 flags0 ASM_REG("$7");
    register s32 flags1 ASM_REG("$6");
    register s32 next ASM_REG("$2");
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
        ASM_KEEP(flags0);
        if (temp) {
            result--;
        }
    }
    next = flags0 & 4;
    ASM_KEEP(result);
    if (!next) {
        return (s16)result;
    }
    temp = flags1 & 2;
    if (temp) {
        result++;
    }
    temp = flags1 & 1;
    ASM_KEEP(flags1);
    if (temp) {
        result--;
    }
    return (s16)result;
}

/* MECHANISM: Frameless leaf; guarded roles hold result/flags in $v1/$a3/$a2.
   A separate $v0 next-mask plus an explicit early return preserves the split CFG
   and both retail sign-extension sites, including the false-edge delay slot. */
