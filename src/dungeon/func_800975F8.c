#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8009CD58_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x36];
    void * unk_4C;
    u8 * unk_50;
} S_8009CD58_0;   /* arg0 in func_8009CD58 */

typedef struct S_8009CD58_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009CD58_1;   /* temp_a0_3 in func_8009CD58 */



s32 func_8009CD58(S_8009CD58_0 *arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_t0;
    register s32 var_a3 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
    register s32 var_mask ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 var_cmp;
    u8 *temp_a0_4;
    s32 temp_a0;
    S_8009CD58_1 *temp_a0_3;

    temp_a2 = arg2 << 16;
    temp_t0 = arg0->unk_14 & arg1;
    var_a3 = temp_t0;
    if (temp_a2 != 0) {
        temp_a0_3 = arg0->unk_4C;
        if (temp_a0_3 != NULL) {
            if (temp_a0_3->unk_01 == 15) {
                temp_a0 = temp_a0_3->unk_00;
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
            temp_a0 = temp_a0_3->unk_00;
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
    temp_a0_4 = arg0->unk_50;
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
        var_a3 = temp_t0 | var_mask;
    }
    return var_a3;
}

/* MECHANISM: True-space CFG recovery turns both apparent func_8009CE04 calls into one local compare join, preserving a frameless leaf.
   A widened lbu local plus edge-local masks pinned to $v0 remove truncations and restore the common branch-delay nop.
   Pinning the accumulator to $a3 leaves the masked base held in $t0 and produces retail's exact $t0-to-$a3 copy. */
