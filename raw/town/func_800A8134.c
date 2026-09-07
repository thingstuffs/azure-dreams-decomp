#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

s32 func_800A5894(void *arg0) {
    if (FIELD(arg0, s32, 8) > -0x400000) {
        goto calculate;
    }
    {
        register s32 result ASM_REG("$2");

        result = 0;
        goto out;
    calculate:
        result = (FIELD(arg0, s16, 0xA) * 0xC00) + 0x30000;
    out:
        return result;
    }
}
