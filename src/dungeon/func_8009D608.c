#include "common.h"

extern s32 D_800E296C[];

void func_800A2D68(u8 *arg0, u16 arg1)
{
    register u32 value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    value = arg0[0x42];
    value = (arg0[0x41] << 8) | value;
    value += arg1;
    if (value > 0xFFFF) {
        value = 0xFFFF;
    }
    arg0[0x41] = value >> 8;
    arg0[0x42] = value;
    D_800E296C[0] |= 0x100000;
}

/* MECHANISM: Keep the frameless leaf and split the low-byte accumulator from the shifted high byte.
   A guarded $v1 accumulator pin gives retail's `or $v1,$v0,$v1` operand order.
   ASM_KEEP marks the accumulator's last real use without adding emitted words. */
