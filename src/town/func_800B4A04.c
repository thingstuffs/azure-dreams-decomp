#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "town.h"

/* Clears the table byte selected by the record's five-bit index. */
void clear_indexed_table_flag(DungeonItemEntry *record) {
    u8 *page = (u8 *)0x80010000;
    page[((record->unk_03 & 0x1F) * 0x54) + 0x303] = 0;
}
