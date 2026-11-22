/* Indexed entry remove and its file-private helper. */
#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "m2c_compat.h"
/* extern */

/* Clears the byte at 0x80010303 plus 0x54 times the low five bits of record byte 3. */
static void clear_indexed_table_flag(DungeonItemEntry *record) {
    u8 *page = (u8 *)0x80010000;
    page[((record->unk_03 & 0x1F) * 0x54) + 0x303] = 0;
}

/* Clears the selected item, releases its type-0x13 table flag, and compacts the pointer list. */
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
