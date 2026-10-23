#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"




/* Return the first entry index matching both bytes, or -1 if none matches. */
s32 find_entry_index_by_grid_bytes(s32 match_byte_1, s32 match_byte_0) {
    s32 result;
    s32 entry_index;
    void **entry_slot;
    TownStateRecord *list_owner;
    TownListEntry *entry;

    result = -1;
    list_owner = town_scene_root->town_state;
    entry_slot = list_owner->entries;
    entry_index = 0;
    if (list_owner->entries[0] != 0) {
        while (1) {
            entry = *entry_slot;
            if ((entry->gridY == match_byte_1) &&
                (entry->gridX == match_byte_0)) {
                result = entry_index;
                break;
            }
            entry_slot = (void **)((s8 *)entry_slot + 4);
            entry_index += 1;
            if (*entry_slot == 0) {
                return result;
            }
        }
    }
    return result;
}
