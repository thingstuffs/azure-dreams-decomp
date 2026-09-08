#include "common.h"

/* Busy-waits for a fixed number of iterations. */
void func_800219C4(void) {
    register s32 remaining ASM_REG("$14");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    remaining = 0x320000;
    do {
        remaining -= 1;
    } while (remaining != 0);
}
