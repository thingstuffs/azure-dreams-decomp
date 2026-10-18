#include "modules/dungeon_ovl_1831370.h"

void write_text_and_advance_selection(s32 objectAddress, s32 updateValue) {
    s32 updatedValue;
    s32 *object;

    object = (s32 *)(objectAddress + 0x20);
    func_8004EAC4(object[5], updateValue, object[2]);
    inventory_set_object_entry_address(object[28], object[5]);
    updatedValue = adjust_selection_by_item_count(1, object[2], object[4]);
    object[2] = updatedValue;
    set_indexed_object_field(object[28], updatedValue);
}
