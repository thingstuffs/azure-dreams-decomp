#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "m2c_compat.h"
#include "town.h"

/* Clear the selected entry and remove its pointer from the null-terminated list. */
void remove_selected_entry_from_list(DungeonItemEntry **list, s32 index) {
    DungeonItemEntry **slot;
    DungeonItemEntry *entry;

    slot = &list[index];
    entry = *slot;
    if (entry->kind == 0x13) {
        clear_indexed_table_flag(entry);
    }
    *(s32 *)*slot = 0;
    if (*slot != NULL) {
        do {
            slot[0] = slot[1];
            slot++;
        } while (*slot != NULL);
    }
}
