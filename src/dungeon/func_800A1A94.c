#include "shared/dungeon_item_entries.h"
#include "common.h"

/* Returns the first entry index with a zero second byte among 64 entries, or -1. */
s32 func_800A71F4(void) {
    u8 *entry;
    s32 entry_index;

    entry_index = 0;
    entry = ((u8 *)D_800E3548);
    do {
        if (entry[1] != 0) {
            entry_index++;
            entry += 4;
            continue;
        }
        return (s16)entry_index;
    } while (entry_index < 0x40);
    return -1;
}
