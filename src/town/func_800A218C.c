#include "common.h"

extern s32 func_8009F750(void *arg0, void *arg1, s32 arg2);
extern s32 D_80010248[];
extern s8 D_80012D52[];

/* Set the entry flag and save the returned table index on success. */
s32 func_8009F8EC(void *entry) {
    s32 entry_index;

    *((u8 *)entry + 3) |= 0x20;
    entry_index = func_8009F750(entry, (void *)0x80010248, 0x14);
    if (entry_index != -1) {
        D_80012D52[0] = entry_index;
    }
    return entry_index;
}

/* MECHANISM: A full-word callee result avoids the spurious s8 sign-extension pair.
   The fixed 0x80010248 argument produces retail's lui/ori address construction.
   At 2.7.2-G0, the branch nop and $at macro store complete the 0x18-frame wrapper. */
