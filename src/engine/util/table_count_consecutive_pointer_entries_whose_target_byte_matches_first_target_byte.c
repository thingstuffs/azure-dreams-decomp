#include "common.h"

typedef struct {
    unsigned char unk0;
    u8 unk1;
} S_8004AFE8;

/*
 * Counts the initial run of records whose field at offset 1 matches the first record, advancing
 * the supplied pointer table.
 */
s32 table_count_consecutive_pointer_entries_whose_target_byte_matches_first_target_byte(S_8004AFE8 **entries)
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
