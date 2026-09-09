#include "common.h"

/* Return the first entry index with a zero status byte, or -1 if all 32 are occupied. */
s32 func_800B5128(void) {
    u8 *entry;
    s32 entry_index;
    u8 *page;

    entry_index = 0;
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    entry = page + 0x3648;
    do {
        if (entry[1] != 0) {
            entry_index++;
            entry += 4;
            continue;
        }
        return (s16)entry_index;
    } while (entry_index < 0x20);
    return -1;
}
