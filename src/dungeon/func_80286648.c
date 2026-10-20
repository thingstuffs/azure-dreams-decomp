#include "dungeon/level/generate.h"

void convert_valid_entry_code_2_to_39(void)
{
    s32 index;
    u8 *base;
    u8 *entry;

    index = D_80012D52;

    if (index >= 0) {
        base = (u8 *)0x800121E8;

        index *= 4;

        entry = (u8 *)((u32)index + (u32)base);

        if (*entry == 2) {
            *entry = 0x39;
        }
    }
}

/* MECHANISM: Frameless leaf; the absolute base selects lui/ori; in-place index *= 4 preserves index-
   first addu order. */
