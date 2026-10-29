#include "common.h"
#include "town/scene.h"

/* Find a matching key in paired entries or return the terminating entry. */
s32 *find_entry_by_paired_key(s32 *entries, s32 key) {
    s32 *entry;

    entry = entries;
    while (entry[1] != 0 && *entry != key) {
        entry += 2;
    }
    return entry;
}
