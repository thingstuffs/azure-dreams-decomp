#ifndef TOWN_SHOP_STATE_H
#define TOWN_SHOP_STATE_H

#include "common.h"


struct S_800B6580_0;
/* set_monster_status_panel_height.c */
void set_monster_status_panel_height(struct S_800B6580_0 *object, s16 height);

s32 set_item_menu_flag_and_return_one(void *state, s32 unused_config);

s32 test_linked_flag(s32 flag_index);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 count_entries_with_flag_20(void *entries);
s32 func_800B44F0(void *state, s32 input);
void set_linked_flag(s32 bit_index);

#include "shared/item_menu.h"
#include "records/Rec_func_800B683C_arg0.h"
void *link_monster_status_display_entries(void *target);
s32 release_monster_status_request_handles(Rec_func_800B683C_arg0 *owner);
void reset_item_menu_object_state(ItemMenuObjectNode *object);

#endif
