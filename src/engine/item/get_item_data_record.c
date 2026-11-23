#include "common.h"
#include "engine/item.h"

/* 19-byte-stride record table at 0x800133E8 (20 entries), immediately
   preceding the 4-byte {short,short} table D_80013564 (indexed the same
   way, by find_item_data_slot()). Not referenced anywhere else as a %hi/%lo
   symbol, so the retail code materializes its base as a raw 32-bit literal
   (lui;ori), not a &symbol reloc (lui;addiu) -- do the same here. */
/* Returns the record for the given category and item, or NULL if absent. */
ItemDataSlotRecord *get_item_data_record(int category, int item)
{
    ItemDataSlotRecord *record = 0;
    int index = find_item_data_slot(category, item);

    if (index < 0x14) {
        record = GAME_STATE->item_data + index;
    }
    return record;
}
