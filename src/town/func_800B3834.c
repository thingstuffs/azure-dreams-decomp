#include "common.h"

extern void func_800B0FCC(void);

s32 func_800B0F94(void *arg0) {
    register u8 flags ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u8 value;

    value = *((u8 *)arg0 + 1);
    if (value == 0x16) {
        func_800B0FCC();
        goto ret_zero;
    }
    if (value != 0x19) {
        goto ret_one;
    }
    flags = *((u8 *)arg0 + 3);
    if (flags & 8) {
        goto ret_zero;
    }
ret_one:
    return 1;
ret_zero:
    return 0;
}
