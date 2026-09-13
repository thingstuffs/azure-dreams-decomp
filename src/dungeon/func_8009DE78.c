#include "common.h"

/* Computes a signed cyclic comparison score for two three-bit masks. */
s32 func_800A35D8(s32 left_mask, s32 right_mask) {
    s16 score;
    s16 left_bits;
    s16 right_bits;
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
    if (left_bits & 2) {
        masked_bit = right_bits & 1;
        if (masked_bit) {
            score++;
        }
        masked_bit = right_bits & 4;
        if (masked_bit) {
            score--;
        }
    }
    masked_bit = left_bits & 4;
    if (!masked_bit) {
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
