#include "common.h"

extern s32 find_item_by_kind_and_type(s32, s32);
extern void set_the_entry_flag_save_returned_table_index_success(s32);

/* set_item_equip_00: Equips the selected item, returning -1 if no item is found. */
s32 set_item_equip_00(s32 first, s32 second) {
    s32 item;

    item = find_item_by_kind_and_type(first, second);
    if (item == 0) {
        return -1;
    }
    set_the_entry_flag_save_returned_table_index_success(item);
}
