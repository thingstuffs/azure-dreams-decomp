/* Item pointer removal. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B4A30, CL:town/func_800B4AB4. */
#include "town/shop/item_pointer_removal_g00615.h"
#include "town/shop.h"

/* Return the first matching value index, or the number of entries searched. */
s32 find_value_index_or_count(DungeonItemEntry **values, DungeonItemEntry *target_value, s32 count) {
    DungeonItemEntry **current_value;
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
void del_t_item_w_ptr(DungeonItemEntry *item_ptr) {
    DungeonItemEntry **items = (DungeonItemEntry **)0x8001029C;
    remove_selected_entry_from_list(items, find_value_index_or_count(items, item_ptr, 0x14));
}
