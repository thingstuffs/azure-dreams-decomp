#include "slus/sort_rank_81540.h"

/* Mark unmarked slots with the one-based positions of matching entries in a NULL-terminated list. */
void stamp_first_matching_entry_ranks(u8 *marks, DungeonItemEntry **entries, s32 match_key)
{
    s32 entry_index;
    DungeonItemEntry *entry;

    entry_index = 0;
    while (*entries != 0) {
        entry = *entries;
        if (entry->kind == match_key) {
            u8 *mark_slot = &marks[entry->unk_00];
            if (*mark_slot == 0) {
                *mark_slot = entry_index + 1;
            }
        }
        entries++;
        entry_index++;
    }
}
