#ifndef TOWN_SHOP_ITEM_POINTER_REMOVAL_G00615_H
#define TOWN_SHOP_ITEM_POINTER_REMOVAL_G00615_H
/* Item pointer removal declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B4A30, CL:town/func_800B4AB4. */

#include "common.h"

#include "shared/dungeon_item_entries.h"

extern u8 *town_item_list[];
extern void remove_selected_entry_from_list(struct DungeonItemEntry **list, s32 index);

/* Functions defined in this translation unit. */
s32 find_value_index_or_count(DungeonItemEntry **values, DungeonItemEntry *target_value, s32 count);
void del_t_item_w_ptr(DungeonItemEntry *item_ptr);

#endif
