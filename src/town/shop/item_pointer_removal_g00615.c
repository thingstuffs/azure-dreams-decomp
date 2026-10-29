/* Item pointer removal (G00615). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B4A30, CL:town/func_800B4AB4. */
#include "town/shop/item_pointer_removal_g00615.h"
#include "town/shop.h"

/* Return the first matching value index, or the number of entries searched. */
s32 find_value_index_or_count(s32 *values, s32 target_value, s32 count) {
    s32 *current_value;
    s32 index;

    current_value = values;
    index = 0;
    while (index < count && target_value != *current_value) {
        index += 1;
        current_value += 1;
    }
    return index;
}

/* del_t_item_w_ptr: Find the town item pointer and delete its table entry. */
void del_t_item_w_ptr(s32 item_ptr) {
    remove_selected_entry_from_list((void *)0x8001029C, find_value_index_or_count((s32 *)0x8001029C, item_ptr, 0x14));
}
