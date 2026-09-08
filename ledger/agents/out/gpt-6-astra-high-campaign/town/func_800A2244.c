#include "common.h"

extern s32 D_8001029C[];

/* Count consecutive nonzero entries, up to twenty. */
s32 func_8009F9A4(void) {
    s32 *entry;
    s32 entry_count;

    do { entry_count = 0; } while (0);
    entry = D_8001029C;
loop:
    if (*entry != 0) {
        entry_count++;
        entry++;
        if (entry_count < 20) {
            goto loop;
        }
    }
    return entry_count;
}
