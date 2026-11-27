#include "town/menu/catalog.h"
#include "town/menu.h"
#include "town/menu/catalog_detail_data.h"
#include "town/menu/catalog_scroll_data.h"

/* Update entry flags from the global value and the entry's table threshold. */
void update_catalog_scroll_availability(CatalogDisplay *entry)
{
    unsigned char flags;

    if (catalog_scroll_offset != 0) {
        entry->scroll_direction_mask |= 1;
    } else {
        entry->scroll_direction_mask &= 0xFE;
    }
    if (catalog_scroll_offset < ((catalog_detail_images[entry->selected_entry].count - 3) << 4)) {
        flags = entry->scroll_direction_mask | 2;
    } else {
        flags = entry->scroll_direction_mask & 0xFD;
    }
    entry->scroll_direction_mask = flags;
}
