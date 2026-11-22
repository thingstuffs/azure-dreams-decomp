#include "common.h"

#include "engine/scene.h"
#include "shared/dungeon_item_entries.h"

extern u8 *town_item_list[];
extern void itm_mon_koyaw_set(s32, void *, void *, s8);

/* Process kind 0x13 entries with nonnegative codes in their indexed records. */
void refresh_monster_items_from_creature_records(void) {
    s32 repeat;
    DungeonItemEntry **cursor;
    DungeonItemEntry *entry;
    s32 record_offset;
    u32 data_page;
    s32 record_code;

    if (town_item_list[0] != 0) {
        data_page = 0x80010000;
        cursor = (DungeonItemEntry **)0x8001029C;
        do {
            entry = *cursor;
            if (entry->kind == 0x13) {
                record_offset = (entry->unk_03 & 0x1F) * 0x54;
                record_code = *(s8 *)(record_offset + data_page + 0x333);
                if (record_code >= 0) {
                    itm_mon_koyaw_set(record_code & 0x3F, entry,
                                      (void *)(record_offset + 0x800102F0), 1);
                }
            }
            cursor++;

            repeat = (*cursor != 0);
        } while (repeat);
    }
}
