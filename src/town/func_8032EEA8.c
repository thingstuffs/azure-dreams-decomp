#include "common.h"

/* Find a matching key in paired entries or return the terminating entry. */
s32 *func_800196A8(s32 *entries, s32 key) {
    s32 *entry;

    entry = entries;
    while (entry[1] != 0 && *entry != key) {
        entry += 2;
    }
    return entry;
}
