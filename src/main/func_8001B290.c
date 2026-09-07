#include "common.h"

/* %hi/%lo access at 0x8009DDD8 (= 0x800A0000 - 0x2228). Incomplete array forces
 * hi/lo rather than $gp; .set binds the overlay-local absolute address. */
extern u8 D_8009DDD8[];
__asm__(".set D_8009DDD8, 0x8009DDD8");

/* Count non-zero s32 heads of the 5×0x80-byte slots starting at D_8009DDD8.
 * Shape: load → increment offset → maybe count++. The increment is free of
 * the loaded value, so it fills the beqz delay slot (retail schedule). A
 * for-loop that increments after the if leaves that delay as nop. */
s32 func_8001B290(void) {
    s32 count;
    s32 offset;
    s32 val;

    count = 0;
    offset = 0;
    do {
        val = *(s32 *)(D_8009DDD8 + offset);
        offset += 0x80;
        if (val != 0) {
            count++;
        }
    } while (offset < 0x280);

    return count;
}
