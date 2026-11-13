#include "common.h"

typedef struct {
    unsigned char unk0;
    u8 unk1;
} S_8004AFE8;

/*
 * Counts the initial run of records whose field at offset 1 matches the first record, advancing
 * the supplied pointer table.
 */
s32 count_entries_matching_first(S_8004AFE8 **entries)
{
    s32 count;
    s32 first_value;
    S_8004AFE8 **entry;

    entry = entries;
    first_value = (*entry)->unk1;
    count = 0;
    while (entry != 0 && (*entry)->unk1 == first_value) {
        entry += 1;
        count += 1;
    }
    return count;
}
