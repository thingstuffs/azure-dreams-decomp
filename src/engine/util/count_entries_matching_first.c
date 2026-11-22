#include "slus/sort_rank_81540.h"

/*
 * Counts the initial run of records whose field at offset 1 matches the first record, advancing
 * the supplied pointer table.
 */
s32 count_entries_matching_first(DungeonItemEntry **entries)
{
    s32 count;
    s32 first_value;
    DungeonItemEntry **entry;

    entry = entries;
    first_value = (*entry)->kind;
    count = 0;
    while (entry != 0 && (*entry)->kind == first_value) {
        entry += 1;
        count += 1;
    }
    return count;
}
