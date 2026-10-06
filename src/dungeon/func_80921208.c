#include "common.h"
extern u8 D_800E3548[];
s32 func_800F6208(s32 key_high, s32 key_low) {
    s32 index;
    s32 key;
    u8 *entry;

    key = (key_high << 8) | (key_low & 0xFF);
    index = 0;
    key &= 0xFFFF;
    entry = D_800E3548;
    while (index < 0x40) {
        if (*(u16 *)entry == key) {
            return 1;
        }
        index++;
        entry += 4;
    }
    return 0;
}

/* MECHANISM: Frameless leaf; an s32 key stays in $a0 across the pointer-induction loop.
   Separate combine, counter-zero, and mask statements consume $a1 before reusing it as the counter.
   That boundary orders move/andi before cdk's two-register D_800E3548 base materialization. */
