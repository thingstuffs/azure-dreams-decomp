#include "common.h"
#include "shared/object_payload.h"
#include "town/menu/catalog_parts.h"
#include "town/menu/animation.h"

/* Initialize 14 objects from table data and override the final two field pairs. */
void layout_catalog_frame(void) {
    {
        CatalogFrameEntry *src_entry;
        ItemMenuPart **object_slot;
        s32 entry_index = 0;
        s16 first_default = 0x10;
        s16 second_default = 0xE0;

        object_slot = catalog_display_node_slots + 0;
        src_entry = catalog_frame_layout;
        do {
            object_slot[entry_index]->handler = src_entry[entry_index].value;
            object_slot[entry_index]->position->x = src_entry[entry_index].x;
            object_slot[entry_index]->position->y = src_entry[entry_index].y;
            ((CatalogDisplayVector *)object_slot[entry_index]->vector)->signed_halves.unk_06 = first_default;
            ((CatalogDisplayVector *)object_slot[entry_index]->vector)->signed_halves.unk_08 = second_default;
            entry_index++;
        } while (entry_index < 0xE);
    }

    {
        CatalogFrameEntry *source_table;
        ItemMenuPart **object_table;

        object_table = catalog_display_node_slots;
        source_table = catalog_frame_layout;
        ((CatalogDisplayVector *)object_table[12]->vector)->unsigned_halves.unk_06 = source_table[12].x;
        ((CatalogDisplayVector *)object_table[12]->vector)->unsigned_halves.unk_08 = source_table[12].y;
        ((CatalogDisplayVector *)object_table[13]->vector)->unsigned_halves.unk_06 = source_table[13].x;
        ((CatalogDisplayVector *)object_table[13]->vector)->unsigned_halves.unk_08 = source_table[13].y;
    }
}
