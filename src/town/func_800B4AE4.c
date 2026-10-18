#include "common.h"

extern void remove_selected_entry_from_list(void *list_addr, s32 index);
extern s32 find_value_index_or_count(void *values, s32 target_value, s32 count);

/* del_t_item_w_ptr: Find the town item pointer and delete its table entry. */
void del_t_item_w_ptr(s32 item_ptr) {
    remove_selected_entry_from_list((void *)0x8001029C, find_value_index_or_count((void *)0x8001029C, item_ptr, 0x14));
}
