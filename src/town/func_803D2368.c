/* Relink of matched town/func_8032EEA8; every changed retail word is a paired relocation. */
#define townFindEntryByPairedKey func_80019368
#include "common.h"

/* Find a matching key in paired entries or return the terminating entry. */
s32 *func_80019368(s32 *entries, s32 key) {
    s32 *entry;

    entry = entries;
    while (entry[1] != 0 && *entry != key) {
        entry += 2;
    }
    return entry;
}
