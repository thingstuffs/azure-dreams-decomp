#include "common.h"

/* Counts entries in a zero-terminated integer array. */
s32 func_800B29A4(s32 *entries) {
    s32 *entry;
    s32 count;

    entry = entries;
    count = 0;
    if (*entry != 0) {
        do {
            entry += 1;
            count += 1;
        } while (*entry != 0);
    }
    return count;
}
