#include "common.h"

/* Returns the index of a matching table entry address, or -1. */
s32 func_80098C48(s32 entry_address) {
    s32 entry_index = 0x13;
    s8 *entry = (s8 *)0x80010294;

    do {
        if ((s32)entry != entry_address) {
            entry_index -= 1;
            entry -= 4;
            continue;
        }
        return (s16)entry_index;
    } while (entry_index >= 0);
    return -1;
}
