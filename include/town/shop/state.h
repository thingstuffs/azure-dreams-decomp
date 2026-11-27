#ifndef TOWN_SHOP_STATE_H
#define TOWN_SHOP_STATE_H

struct TownObjectRecord;
struct ColliderView;
void start_move_toward_view_reference(struct TownObjectRecord *state, struct ColliderView *collider);

#include "town/shop/object.h"
#include "common.h"


struct S_800B6580_0;
/* set_monster_status_panel_height.c */
void set_monster_status_panel_height(struct S_800B6580_0 *object, s32 height);

s32 set_item_menu_flag_and_return_one(void *state, void *unused_config);

s32 test_indexed_flag(s32 flag_index);

struct ShopWindow;
/* update_shop_page_edge_flags.c */
void update_shop_page_edge_flags(struct ShopWindow *window);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct DungeonItemEntry;
s32 count_equipped_entries(struct DungeonItemEntry *entries);
s32 initialize_storage_window_resources(void *state, s32 input);
void set_indexed_flag(s32 bit_index);
void clear_indexed_flag(s32 bit_index);

#include "shared/item_menu.h"
#include "records/Rec_func_800B683C_arg0.h"
void *link_monster_status_display_entries(void *target);
s32 release_monster_status_request_handles(ShopFirstCallbackObject *owner);
void release_item_menu_child_object(ItemMenuObjectNode *object);

/* Address-qualified entries of distinct diagnostic devkit builds. */
s32 test_linked_flag_80700c7c(s32 flag_index);
void set_linked_flag_80700cd0(s32 bit_index);
s32 test_linked_flag_80701134(s32 flag_index);
void set_linked_flag_80700d1c(s32 bit_index);
s32 test_linked_flag_80700dc0(s32 flag_index);

/* Additional diagnostic copies recovered while resolving import floors. */
s32 test_linked_flag_80000c6c(s32 index);

void apply_shop_transaction(void *entries, s32 entry_mode);
void fade_out_shop_window(void *object_arg);

#endif
