#include "common.h"
extern u8 D_8008BA00[];

extern u8 D_800FC418;

/* Select and store an address based on the global byte value. */
s32 func_8008BED8(void *object) {
    u8 value = D_800FC418;
    register u32 result_m ASM_REG("$2");

    if (value == 0xFF) {
        result_m = 0x80090000;

        result_m = (u32)D_8008BA00;
        goto merge;
    }
    if (value != 0) {
        return 0x80090000;
    }
    {

        result_m = 0x80090000;
        ASM_KEEP(result_m);
        result_m -= 0x43A8;
    }
merge: {

        *(u32 *)((u8 *)object + 0x68) = result_m;
        return result_m;
    }
}
