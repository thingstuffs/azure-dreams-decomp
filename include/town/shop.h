#ifndef TOWN_SHOP_H
#define TOWN_SHOP_H

#include "common.h"
#include "shared/item_menu.h"


/* get_player_homerank.c */
s32 get_player_homerank(void);

struct S_800AE56C_0;
void dispatch_item_menu_entry_callback(struct S_800AE56C_0 *state, s32 callback_arg);
void invoke_item_menu_offset_handler(u8 *object, s32 callback_arg);

void initialize_item_menu_request_state(void *state, s32 base_value);


s32 count_town_items(void);
void fill_ten_paged_output_slots(s32 **outputs, s32 *page_info, s32 record_table);

struct ItemMenuPart;
struct ItemMenuObject;
void item_menu_no_op(struct ItemMenuPart **parts, struct ItemMenuObject *object);

#include "town/shop/storage_menu.h"

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(void);

void * create_item_menu_object(s32 selector);

s32 advance_shop_entry_index_107(s32 index);
s32 count_free_item_slots(void);

#endif
