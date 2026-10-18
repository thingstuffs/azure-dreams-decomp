#include "common.h"

extern s32 D_80100AA0[];

/* Clears all 20 entries in D_80100AA0. */
void clear_entry_table(void) {
    s32 *entry;
    s32 index;

    index = 19;
    entry = D_80100AA0;
    entry += 19;
    do {
        *entry = 0;
        index--;
        entry--;
    } while (index >= 0);
}
