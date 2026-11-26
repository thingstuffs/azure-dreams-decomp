#include "common.h"
#include "shared/resident_resources.h"
#include "m2c_compat.h"
#include "slus.h"
#include "town/shop.h"
#include "town/shop/shop_window_layout_g00610.h"


/* Apply D_800792DC using the linked value and set the linked target to cached_item_secondary_cursor. */
void apply_linked_record_defaults(AlternateStorageOwner *record) {
    initialize_scaled_entry_cursor(&record->cursor, &shop_cursor_template, (s32 *)&record->parts[4]->handler);
    record->parts[5]->handler = cached_item_secondary_cursor;
}
