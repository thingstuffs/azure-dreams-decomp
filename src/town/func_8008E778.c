#include "common.h"

extern u8 D_800FC418;

s32 func_8008BED8(void *arg0) {
    u8 value = D_800FC418;

    if (value == 0xFF) {
        register u32 result ASM_REG("$2") = 0x80090000;

        ASM_KEEP(result);
        result -= 0x4600;
        goto merge;
    }
    ASM_SCHED_BARRIER();
    if (value != 0) {
        return 0x80090000;
    }
    {
        register u32 result ASM_REG("$2");

        result = 0x80090000;
        ASM_KEEP(result);
        result -= 0x43A8;
    }
merge: {
        register u32 result ASM_REG("$2");

        *(u32 *)((u8 *)arg0 + 0x68) = result;
        return result;
    }
}
