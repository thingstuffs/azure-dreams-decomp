#include "common.h"
#include "town/shop/item_lookup.h"
#include "town/shop.h"


extern u8 *find_unused_default_pool_slot(void);

/* Copies a record into the pointer table and initializes extra data for tag 0x13. */
void install_slot_record_with_extra_data(s32 entry_index, void *source) {
    const u8 *source_bytes = source;
    u8 *record;
    s32 tag;
    s32 data_slot;

    record = find_unused_default_pool_slot();
    record[0] = source_bytes[0];
    record[1] = source_bytes[1];
    record[2] = source_bytes[2];
    tag = record[1];
    record[3] = source_bytes[3];
    if (tag == 0x13) {
        data_slot = find_first_vacant_record((const u8 *)GAME_STATE->item_monsters, 0x14);
        *(TownSlotSnapshot *)(0x800102F0 + data_slot * 0x54) = town_slot_snapshot;
        record[3] = (record[3] & 0xC0) | data_slot;
    }
    GAME_STATE->item_list[entry_index] = (DungeonItemEntry *)record;
    GAME_STATE->item_list[entry_index + 1] = 0;
}
