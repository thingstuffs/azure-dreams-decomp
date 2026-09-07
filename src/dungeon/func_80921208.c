#include "common.h"

extern u8 D_800E3548[];

s32 func_800F6208(s32 arg0, s32 arg1) {
    s32 index;
    s32 result;
    s32 key;
    u8 *entry;

    key = (arg0 << 8) | (arg1 & 0xFF);
    index = 0;
    key &= 0xFFFF;
    entry = D_800E3548;
    do {
        if (*(u16 *)entry == key) {
            result = 1;
            goto done;
        }
        index++;
        entry += 4;
    } while (index < 0x40);
    result = 0;
done:
    return result;
}

/* MECHANISM: Frameless leaf; an s32 key stays in $a0 across the pointer-induction loop.
   Separate combine, counter-zero, and mask statements consume $a1 before reusing it as the counter.
   That boundary orders move/andi before cdk's two-register D_800E3548 base materialization. */
