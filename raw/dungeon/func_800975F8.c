#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

s32 func_8009CD58(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_t0;
    register s32 var_a3 ASM_REG("$7");
    register s32 var_mask ASM_REG("$2");
    s32 var_cmp;
    u8 *temp_a0_4;
    s32 temp_a0;
    void *temp_a0_3;

    temp_a2 = arg2 << 16;
    temp_t0 = FIELD(arg0, u16, 0x14) & arg1;
    var_a3 = temp_t0;
    if (temp_a2 != 0) {
        temp_a0_3 = FIELD(arg0, void *, 0x4C);
        if (temp_a0_3 != NULL) {
            if (FIELD(temp_a0_3, u8, 1) == 15) {
                temp_a0 = FIELD(temp_a0_3, u8, 0);
                if (temp_a0 == 5) {
                    var_mask = arg1 & 1;
                    goto block_16;
                }
                if (temp_a0 == 6) {
                    var_mask = arg1 & 2;
                    goto block_16;
                }
                var_cmp = 7;
                goto block_15;
            }
            temp_a0 = FIELD(temp_a0_3, u8, 0);
            if (temp_a0 == 6) {
                var_mask = arg1 & 1;
                goto block_16;
            }
            if (temp_a0 == 7) {
                var_mask = arg1 & 2;
                goto block_16;
            }
            var_cmp = 8;
            goto block_15;
        }
        return var_a3;
    }
    temp_a0_4 = FIELD(arg0, u8 *, 0x50);
    if (temp_a0_4 != NULL) {
        temp_a0 = *temp_a0_4;
        if (temp_a0 == 8) {
            var_mask = arg1 & 1;
            goto block_16;
        }
        if (temp_a0 == 9) {
            var_mask = arg1 & 2;
            goto block_16;
        }
        var_cmp = 10;
block_15:
        if (temp_a0 != var_cmp) {
            return var_a3;
        }
        var_mask = arg1 & 4;
block_16:
        ASM_KEEP(var_mask);
        var_a3 = temp_t0 | var_mask;
    }
    ASM_KEEP(var_a3);
    return var_a3;
}

/* MECHANISM: True-space CFG recovery turns both apparent func_8009CE04 calls into one local compare join, preserving a frameless leaf.
   A widened lbu local plus edge-local masks pinned to $v0 remove truncations and restore the common branch-delay nop.
   Pinning the accumulator to $a3 leaves the masked base held in $t0 and produces retail's exact $t0-to-$a3 copy. */
