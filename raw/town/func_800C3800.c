#include "common.h"

extern u8 D_800D0000[];

s32 func_800C0F60(s32 arg0) {
    u8 *entry;
    s32 value;
    s32 count;

    entry = D_800D0000;
    ASM_KEEP(entry);
    count = 0;
    if (*(s16 *)(entry + 0x4094) != 0) {
        entry += 0x4094;
        ASM_MEM_BARRIER();
        value = *(s16 *)entry;
loop:
        if (value != arg0) {
            entry += 10;
            value = *(s16 *)entry;
            count++;
            if (value != 0) {
                goto loop;
            }
        }
    }
    return count;
}

/* MECHANISM: A mutable D_800D0000 page pointer holds $v1: first load uses +0x4094,
   then the pointer advances once. ASM_KEEP blocks symbol folding into an $at macro,
   while ASM_MEM_BARRIER preserves the required loop-entry reload in this frameless leaf. */
