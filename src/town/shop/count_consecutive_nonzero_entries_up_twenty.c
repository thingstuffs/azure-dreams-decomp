#include "common.h"
#include "town/shop.h"

/* Counts the initial nonzero words at 0x8001029C, stopping at the first zero or after 20 entries. */
s32 count_consecutive_nonzero_entries_up_twenty(void) {
    s32 *entry;
    s32 i;

    entry = (s32 *)0x80010000;
    for (i = 0; i < 20 && entry[167 + i] != 0; i++) {
    }
    return i;
}
