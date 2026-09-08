#include "common.h"

/* Struct shared with func_8004AFE8 sibling: byte field unk0 (index) and
 * unk1 (match key). */
typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;

/* Mark unmarked slots with the one-based positions of matching entries in a NULL-terminated list. */
void func_8004B028(u8 *marks, S_8004AFE8 **entries, s32 matchKey)
{
    s32 entryIndex;
    S_8004AFE8 *entry;

    entryIndex = 0;
    while (*entries != 0) {
        entry = *entries;
        if (entry->unk1 == matchKey) {
            u8 *markSlot = &marks[entry->unk0];
            if (*markSlot == 0) {
                *markSlot = entryIndex + 1;
            }
        }
        entries++;
        entryIndex++;
    }
}
