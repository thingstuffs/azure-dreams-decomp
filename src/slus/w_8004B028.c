#include "common.h"

/* Struct shared with tableCountConsecutivePointerEntriesWhoseTargetByteMatchesFirstTargetByte sibling: byte field unk0 (index) and
 * unk1 (match key). */
typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;

/* Mark unmarked slots with the one-based positions of matching entries in a NULL-terminated list. */
void stampFirstMatchingEntryRanks(u8 *marks, S_8004AFE8 **entries, s32 match_key)
{
    s32 entry_index;
    S_8004AFE8 *entry;

    entry_index = 0;
    while (*entries != 0) {
        entry = *entries;
        if (entry->unk1 == match_key) {
            u8 *mark_slot = &marks[entry->unk0];
            if (*mark_slot == 0) {
                *mark_slot = entry_index + 1;
            }
        }
        entries++;
        entry_index++;
    }
}
