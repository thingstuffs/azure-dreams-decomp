#include "common.h"

s32 func_800B5128(void) {
    u8 *entry;
    s32 i;
    u8 *page;

    i = 0;
    page = (u8 *)0x800E0000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    entry = page + 0x3648;
    do {
        if (entry[1] != 0) {
            i++;
            entry += 4;
            continue;
        }
        return (s16)i;
    } while (i < 0x20);
    return -1;
}
