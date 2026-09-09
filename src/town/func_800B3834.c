#include "common.h"

/* Check whether the entry passes the type and flag filter. */
s32 func_800B0F94(void *entry) {
    register u8 flags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 value;

    value = *((u8 *)entry + 1);
    if (value == 0x16) {
        ASM_SCHED_BARRIER();
        goto ret_zero;
    }
    if (value != 0x19) {
        goto ret_one;
    }
    flags = *((u8 *)entry + 3);
    if (flags & 8) {
        goto ret_zero;
    }
ret_one:
    return 1;
ret_zero:
    return 0;
}
