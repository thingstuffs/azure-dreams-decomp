#include "common.h"

extern u8 D_800D0000[];

/* Return the index of the matching value or the terminating zero in the entry table. */
s32 func_800C0F60(s32 target_value) {
    u8 *entry;
    s32 entry_value;
    s32 entry_index;

    entry = D_800D0000;
    ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    entry_index = 0;
    if (*(s16 *)(entry + 0x4094) != 0) {
        entry += 0x4094;
        entry_value = *(s16 *)entry;
loop:
        if (entry_value != target_value) {
            entry += 10;
            entry_value = *(s16 *)entry;
            entry_index++;
            if (entry_value != 0) {
                goto loop;
            }
        }
    }
    return entry_index;
}

/* MECHANISM: A mutable D_800D0000 page pointer holds $v1: first load uses +0x4094,
   then the pointer advances once. ASM_KEEP blocks symbol folding into an $at macro,
   while ASM_MEM_BARRIER preserves the required loop-entry reload in this frameless leaf. */
