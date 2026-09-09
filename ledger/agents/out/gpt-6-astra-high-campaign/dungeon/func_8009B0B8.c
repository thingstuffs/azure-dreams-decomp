#include "common.h"

extern s32 func_80065F90();

/* Computes a rounded direction between two points and updates flag bit 1. */
s32 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags) {
    s32 angle;
    u16 new_flags;

    {
        s32 direction;
        direction = func_80065F90(end_y - start_y, end_x - start_x, end_x, end_y);
        angle = direction;
        ASM_KEEP_NV(direction);   /* Required for byte-exact register allocation. */
        if ((direction & 0x1FF) < 0x100) {
            goto in_range;
        }
    }
    new_flags = *flags | 2;
    goto store;
in_range:
    new_flags = *flags & 0xFFFD;
store:
    *flags = new_flags;
    return (angle + 0x100) & 0xE00;
}
