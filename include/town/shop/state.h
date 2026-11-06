#ifndef TOWN_SHOP_STATE_H
#define TOWN_SHOP_STATE_H

#include "common.h"


struct S_800B6580_0;
/* set_monster_status_panel_height.c */
void set_monster_status_panel_height(struct S_800B6580_0 *object, s16 height);

s32 set_item_menu_flag_and_return_one(void *state, void *unused_config);

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

/* Address-qualified entries of distinct diagnostic devkit builds; docs/evidence/r141w_town_dev.md. */
s32 test_linked_flag_80700c7c(s32 flag_index);
void set_linked_flag_80700cd0(s32 bit_index);
s32 test_linked_flag_80701134(s32 flag_index);
void set_linked_flag_80700d1c(s32 bit_index);
s32 test_linked_flag_80700dc0(s32 flag_index);

/* Additional diagnostic copies recovered while resolving import floors. */
s32 test_linked_flag_80000c6c(s32 index);

void process_lshop_entries(void *entries, s32 entry_mode);
#endif
