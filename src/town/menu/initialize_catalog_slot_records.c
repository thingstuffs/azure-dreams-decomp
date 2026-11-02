#include "common.h"
#include "shared/object_payload.h"
#include "town/menu/catalog_parts.h"
#include "town/menu.h"

/* Initializes fourteen objects from the source table and overrides the last two value pairs. */
void initialize_catalog_slot_records(void) {
    {
        CatalogFrameEntry *source_entry;
        u8 *address_base;
        ItemMenuPart **object_slot;
        s32 entry_index = 0;
        s16 default_first = 0x10;
        s16 default_second = 0xE0;

        address_base = (u8 *)&catalog_display_node_slots;
        object_slot = (ItemMenuPart **)(address_base + 0x38);
        source_entry = catalog_frame_layout;
        do {
            object_slot[entry_index]->handler = 0;
            object_slot[entry_index]->position->x = source_entry[entry_index].x;
            object_slot[entry_index]->position->y = source_entry[entry_index].y;
            ((CatalogDisplayVector *)object_slot[entry_index]->vector)->signed_halves.unk_06 = default_first;
            ((CatalogDisplayVector *)object_slot[entry_index]->vector)->signed_halves.unk_08 = default_second;
            entry_index++;
        } while (entry_index < 0xE);
    }

    {
        CatalogFrameEntry *source_table;
        ItemMenuPart **object_table;

        object_table = catalog_display_node_slots;
        source_table = catalog_frame_layout;
        ((CatalogDisplayVector *)object_table[26]->vector)->unsigned_halves.unk_06 = source_table[12].x;
        ((CatalogDisplayVector *)object_table[26]->vector)->unsigned_halves.unk_08 = source_table[12].y;
        ((CatalogDisplayVector *)object_table[27]->vector)->unsigned_halves.unk_06 = source_table[13].x;
        ((CatalogDisplayVector *)object_table[27]->vector)->unsigned_halves.unk_08 = source_table[13].y;
    }
}
