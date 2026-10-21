/* Item equip selection (G00560). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A218C. */
#include "town/shop/item_equip_selection_g00560.h"

/* Set the entry flag and save the returned table index on success. */
s32 set_the_entry_flag_save_returned_table_index_success(void *entry) {
    s32 entry_index;

    *((u8 *)entry + 3) |= 0x20;
    entry_index = get_index_address_in_range_four_byte_slots_n_1(entry, (void *)0x80010248, 0x14);
    if (entry_index != -1) {
        *(s8 *)0x80012D52 = entry_index;
    }
    return entry_index;
}

/* set_item_equip_00: Equips the selected item, returning -1 if no item is found. */
s32 set_item_equip_00(s32 first, s32 second) {
    s32 item;

    item = find_item_by_kind_and_type(first, second);
    if (item == 0) {
        return -1;
    }
    set_the_entry_flag_save_returned_table_index_success((void *)item);
}
