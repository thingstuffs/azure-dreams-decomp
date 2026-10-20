#include "common.h"

/* Count consecutive nonzero entries, up to twenty. */
s32 count_consecutive_nonzero_entries_up_twenty(void) {
    s32 *entry;
    s32 i;

    entry = (s32 *)0x80010000;
    for (i = 0; i < 20 && entry[167 + i] != 0; i++) {
    }
    return i;
}
