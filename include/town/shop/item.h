#ifndef TOWN_SHOP_ITEM_H
#define TOWN_SHOP_ITEM_H
/* Prototypes of the functions defined in src/town/shop/item/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/item_menu.h"
#include "shared/object_node.h"

struct ItemMenuObject;
struct ItemMenuPart;
struct ItemMenuTransition;
struct S_800AE56C_0;
struct S_800AEBC4_4;
struct S_800AEBC4_6;
struct S_800AFF00_0;
struct S_800AFF00_4;
struct S_800B0418_0;
struct S_800B0700_0;
struct ShopWindow;

/* allocate_paged_shop_item_list.c */
void *allocate_paged_shop_item_list(s32 parent, s32 selected_index, s32 item_count, s32 page_index, s32 last_page, s32 item_base, s32 display_mode);

/* change_item_menu_selection.c */
void change_item_menu_selection(ObjectNodeHeader *object, s32 value_arg, s32 reset_value);

/* clear_item_menu_entry_groups.c */
void clear_item_menu_entry_groups(ItemMenuPart **parts);

/* dispatch_item_menu_data_update.c */
void dispatch_item_menu_data_update(void *data);

/* dispatch_item_menu_entry_callback.c */
s32 dispatch_item_menu_entry_callback(struct S_800AE56C_0 *state, s32 callback_arg);

/* find_item_by_key_pair.c */
u8 *find_item_by_key_pair(s32 first_key, s32 second_key);

/* get_item_chk.c */
s32 func_8009F6E4(void);
s32 get_item_chk(void);

/* get_item_menu_table_entry.c */
s32 get_item_menu_table_entry(s32 index);

/* initialize_item_menu_linked_blocks.c */
void initialize_item_menu_linked_blocks(struct S_800AFF00_4 *state, struct S_800AFF00_0 *primary, DisplayPositionWords *secondary);

/* initialize_item_menu_linked_record_vectors.c */
void initialize_item_menu_linked_record_vectors(struct S_800AEBC4_6 *vectors, struct S_800AEBC4_4 *config, s32 *position_data, s32 *secondary_data, s32 x, s32 y);

/* initialize_item_menu_list_display.c */
void initialize_item_menu_list_display(s32 objectData, s32 owner, s32 listConfig, s32 entryCount, s32 x, s32 y, s32 entryIds);

/* initialize_item_menu_list_entries.c */
void initialize_item_menu_list_entries(void *list);

/* initialize_item_menu_panel_rectangle.c */
void initialize_item_menu_panel_rectangle(void *record);

/* initialize_item_menu_record_fields.c */
void initialize_item_menu_record_fields(void *record, s32 value_3c, s32 value_34, s32 value_28, s32 value_38);

/* initialize_item_menu_scene_value.c */
s32 initialize_item_menu_scene_value(s32 value);

/* invoke_item_menu_offset_handler.c */
s32 invoke_item_menu_offset_handler(u8 *object, s32 callback_arg);

/* item_menu_no_op.c */
void item_menu_no_op(struct ItemMenuPart **parts, struct ItemMenuObject *object);

/* item_menu_return_zero.c */
s32 item_menu_return_zero(void);

/* layout_item_menu_lower_item_columns.c */
void layout_item_menu_lower_item_columns(ItemMenuPart **parts);

/* layout_item_menu_lower_pair_columns.c */
void layout_item_menu_lower_pair_columns(ItemMenuPart **parts);

/* layout_item_menu_upper_pair_columns.c */
void layout_item_menu_upper_pair_columns(ItemMenuPart **parts);

/* link_item_menu_display_entries.c */
void *link_item_menu_display_entries(s32 entries);

/* populate_current_item_menu_page.c */
void populate_current_item_menu_page(ItemMenuObject *state);

/* populate_item_menu_lower_entries.c */
void populate_item_menu_lower_entries(ItemMenuObject *context);

/* populate_item_menu_page_entries.c */
void populate_item_menu_page_entries(ItemMenuPart **parts, ItemMenuObject *object);

/* populate_shop_item_rows.c */
void populate_shop_item_rows(struct ShopWindow *ctx);

/* process_item_menu_selected_entry.c */
void process_item_menu_selected_entry(ItemMenuObject *record);

/* run_item_menu_record_handlers.c */
void run_item_menu_record_handlers(void *record_payload);

/* schedule_item_menu_child_release.c */
void schedule_item_menu_child_release(struct S_800B0700_0 *object);

/* serch_item_plown.c */
s32 serch_item_plown(s32 item_kind, s32 item_type);

/* set_item_menu_data_pointer.c */
void set_item_menu_data_pointer(ItemMenuStateNode *owner);

/* set_item_menu_entry_coordinates.c */
void set_item_menu_entry_coordinates(ItemMenuObject *object);

/* set_item_menu_record_active.c */
void set_item_menu_record_active(struct S_800B0418_0 *object);

/* set_item_menu_secondary_handler.c */
void set_item_menu_secondary_handler(ItemMenuStateNode *owner);

/* tick_item_menu_selection_delay.c */
void tick_item_menu_selection_delay(struct ItemMenuTransition *state);

/* update_item_menu_enabled_record.c */
void update_item_menu_enabled_record(ItemMenuObject *object);

/* update_item_menu_record_g01150.c */
void update_item_menu_record(ItemMenuObject *record);
void *place_selected_item_menu_entry(ItemMenuObject *entry);
void store_item_menu_check_result(ItemMenuObject *record_data);
void update_item_menu_selection(ItemMenuObject *obj);
void reset_item_menu_entity_state(ItemMenuObject *entity);
void advance_item_menu_step(ItemMenuObject *object);

#endif
