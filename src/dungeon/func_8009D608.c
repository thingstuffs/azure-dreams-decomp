#include "common.h"

extern s32 D_800E296C[];

/* Adds to the big-endian value at offset 0x41, saturates at 0xFFFF, and sets the update flag. */
void func_800A2D68(u8 *record, u16 amount)
{
    register u32 value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    value = record[0x42];
    value = (record[0x41] << 8) | value;
    value += amount;
    if (value > 0xFFFF) {
        value = 0xFFFF;
    }
    record[0x41] = value >> 8;
    record[0x42] = value;
    D_800E296C[0] |= 0x100000;
}

/* MECHANISM: Keep the frameless leaf and split the low-byte accumulator from the shifted high byte.
   A guarded $v1 accumulator pin gives retail's `or $v1,$v0,$v1` operand order.
   ASM_KEEP marks the accumulator's last real use without adding emitted words. */
