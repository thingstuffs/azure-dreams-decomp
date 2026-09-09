#include "common.h"

extern s32 D_80100AA0[];

/* Shift entries left until a free entry or the limit, then clear the tail. */
void func_800A04B4(void) {
    s32 entry_index;
    s32 *entries = &D_80100AA0[0];
    s32 *write_entry;
    s32 *src;

    entry_index = 0;
    write_entry = entries;
    src = entries + 1;
loop:
    if (((u8 *)write_entry)[1] != 0) {
        *write_entry = *src;
        src++;
        entry_index++;
        write_entry++;
        if (entry_index < 19) {
            goto loop;
        }
    }
    do {
        entries[entry_index] = 0;
    } while (0);
}
