#include "common.h"
#include "town/shop/item_lookup.h"
#include "town/shop.h"


extern u8 *find_unused_default_pool_slot(void);

/* Copies a record into the pointer table and initializes extra data for tag 0x13. */
void install_slot_record_with_extra_data(s32 entry_index, void *source) {
    u8 *record;
    s32 tag;
    s32 data_slot;

    record = find_unused_default_pool_slot();
    record[0] = ((u8 *)source)[0];
    record[1] = ((u8 *)source)[1];
    record[2] = ((u8 *)source)[2];
    tag = record[1];
    record[3] = ((u8 *)source)[3];
    if (tag == 0x13) {
        data_slot = find_first_vacant_record((void *)GAME_STATE->item_monsters, 0x14);
        *(TownSlotSnapshot *)(0x800102F0 + data_slot * 0x54) = town_slot_snapshot;
        record[3] = (record[3] & 0xC0) | data_slot;
    }
    GAME_STATE->item_list[entry_index] = (void *)record;
    GAME_STATE->item_list[entry_index + 1] = 0;
}
