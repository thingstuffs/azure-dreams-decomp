#include "common.h"
#include "m2c_compat.h"
#include "town/shop/item.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"


/* Set four record values and initialize its trailing data. */
void initialize_item_menu_record_fields(void *record_arg, s32 value_3c, s32 value_34, s32 value_28, s32 value_38) {
    ItemMenuTransition *record = record_arg;

    record->unk_3C = value_3c;
    record->unk_34 = value_34;
    record->entry_count = value_28;
    record->entry_data_address = value_38;
    init_item_menu_sub_record_pair(record_arg + 0x40);
}
