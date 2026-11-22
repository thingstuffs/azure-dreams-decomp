#include "common.h"
#include "m2c_compat.h"
#include "town/shop/state.h"

#include "shared/dungeon_item_entries.h"

/* Count entries with flag 0x20, excluding IDs 0x17 and 0x18. */
s32 count_equipped_entries(DungeonItemEntry *entries) {
    s32 count;
    DungeonItemEntry *entry;
    u8 entry_id;

    entry_id = entries->kind;
    count = 0;
    if (entry_id != 0) {
        entry = entries;
        do {
            if ((entry->unk_03 & 0x20) && ((u32) (entry_id - 0x17) >= 2U)) {
                count += 1;
            }
            entry++;
            entry_id = entry->kind;
        } while (entry_id != 0);
    }
    return count;
}
