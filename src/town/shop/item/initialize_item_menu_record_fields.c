#include "common.h"
#include "m2c_compat.h"
#include "town/shop/item.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"


/* Set four record values and initialize its trailing data. */
void initialize_item_menu_record_fields(ItemMenuTransition *record, ObjectNodeHeader *owner, s32 value_34, s32 value_28, u8 *entry_ids) {
    record->owner = owner;
    record->unk_34 = value_34;
    record->entry_count = value_28;
    record->entry_ids = entry_ids;
    init_item_menu_sub_record_pair(&record->row_data);
}
