#ifndef TOWN_SHOP_ITEM_EQUIP_SELECTION_G00560_H
#define TOWN_SHOP_ITEM_EQUIP_SELECTION_G00560_H
/* Item equip selection declarations (G00560). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A218C. */

#include "common.h"

extern s32 get_index_address_in_range_four_byte_slots_n_1(void *target_addr, void *slot_addr, s32 slot_count);
extern s32 find_item_by_kind_and_type(s32, s32);

/* Functions defined in this translation unit. */
s32 set_the_entry_flag_save_returned_table_index_success(void *entry);
s32 set_item_equip_00(s32 first, s32 second);

#endif
