#include "common.h"

extern s8 D_800E2970[0x14];

/* Return the indexed entry value when its condition is nonzero, or zero otherwise. */
s32 func_8009FCAC(s16 entry_index) {
    s32 value;
    s32 value_2;
    s32 value_3;

    value = 0;
    if (entry_index >= 0) {
        s8 *entry;

        value_2 = (s32)&D_800E2970;
        entry = (s8 *)value_2 + entry_index * 0x14;
        value_3 = *(s16 *)(entry + 0xA);
        if (value_3 == 0) {
            return 0;
        }
        value = *(s32 *)(entry + 0x10);
    }
    return value;
}

/* MECHANISM: Frameless leaf; one guarded $v0 carrier spans zero, global base,
   halfword condition, and result, while a guarded $v1 holds the entry.
   Assigning the halfword before the literal-zero guard preserves both zero delay slots. */
