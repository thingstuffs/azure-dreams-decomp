#include "common.h"

/* Computes a signed cyclic comparison score for two three-bit masks. */
s32 func_800A35D8(s32 left_mask, s32 right_mask) {
    register s32 score ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 left_bits ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s16 right_bits;
    register s32 left_high_bit ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 masked_bit;

    score = 0;
    left_bits = left_mask;
    right_bits = right_mask;
    left_mask &= 1;
    if (left_mask) {
        masked_bit = right_mask & 4;
        left_mask = masked_bit != 0;
        score = left_mask;
        masked_bit = right_mask & 2;
        if (masked_bit) {
            score = left_mask - 1;
        }
    }
    masked_bit = left_bits & 2;
    if (masked_bit) {
        masked_bit = right_bits & 1;
        if (masked_bit) {
            score++;
        }
        masked_bit = right_bits & 4;
        if (masked_bit) {
            score--;
        }
    }
    left_high_bit = left_bits & 4;
    if (!left_high_bit) {
        return (s16)score;
    }
    masked_bit = right_bits & 2;
    if (masked_bit) {
        score++;
    }
    masked_bit = right_bits & 1;
    if (masked_bit) {
        score--;
    }
    return (s16)score;
}

/* MECHANISM: Frameless leaf; guarded roles hold result/flags in $v1/$a3/$a2.
   A separate $v0 next-mask plus an explicit early return preserves the split CFG
   and both retail sign-extension sites, including the false-edge delay slot. */
