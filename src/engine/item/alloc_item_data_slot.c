#include "common.h"
#include "shared/resident_resources.h"
#include "engine/item.h"


/* Stores two values in the selected slot and returns the corresponding record. */
ItemDataSlotRecord *alloc_item_data_slot(s16 first_value, s16 second_value)
{
    ItemDataSlotRecord *record = 0;
    s32 slot = find_item_data_slot(0, 0);

    if (slot < 0x14) {
        record = GAME_STATE->item_data + slot;
        GAME_STATE->item_data_keys[slot].a = first_value;
        GAME_STATE->item_data_keys[slot].b = second_value;
    }

    return record;
}
