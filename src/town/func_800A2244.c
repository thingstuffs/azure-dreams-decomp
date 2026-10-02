#include "common.h"

/* Count consecutive nonzero entries, up to twenty. */
s32 func_8009F9A4(void) {
    s32 *entry;
    s32 i;

    entry = (s32 *)0x80010000;
    for (i = 0; i < 20 && entry[167 + i] != 0; i++) {
    }
    return i;
}
