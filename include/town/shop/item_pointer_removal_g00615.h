#ifndef TOWN_SHOP_ITEM_POINTER_REMOVAL_G00615_H
#define TOWN_SHOP_ITEM_POINTER_REMOVAL_G00615_H
/* Item pointer removal declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - town/func_800B4A30, town/func_800B4AB4. */

#include "common.h"

extern void remove_selected_entry_from_list(void *list_addr, s32 index);

/* Functions defined in this translation unit. */
s32 find_value_index_or_count(void **values, void *target_value, s32 count);
void del_t_item_w_ptr(void *item_ptr);

#endif
