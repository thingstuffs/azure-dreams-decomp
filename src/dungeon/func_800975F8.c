#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_8009CD58_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009CD58_1;   /* temp_a0_3 in func_8009CD58 */



s32 func_8009CD58(Rec_D_800E3D7C *arg0, s32 arg1, s32 arg2) {
    s32 temp_a2;
    s32 temp_t0;
    register s32 var_a3 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 var_mask ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 var_cmp;
    u8 *temp_a0_4;
    s32 temp_a0;
    S_8009CD58_1 *temp_a0_3;

    temp_a2 = arg2 << 16;
    temp_t0 = arg0->unk_14.as_u16 & arg1;
    var_a3 = temp_t0;
    if (temp_a2 != 0) {
        temp_a0_3 = arg0->unk_4C.as_pv;
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
    temp_a0_4 = arg0->unk_50.at00_pu8.v;
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
