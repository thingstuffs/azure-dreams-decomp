#ifndef TOWN_SHOP_H
#define TOWN_SHOP_H

#include "common.h"

#include "town/shop/grid_menu.h"
#include "shared/item_menu.h"


/* get_player_homerank.c */
s32 get_player_homerank(void);

struct S_800AE56C_0;
s32 dispatch_item_menu_entry_callback(struct S_800AE56C_0 *state, s32 callback_arg);
s32 invoke_item_menu_offset_handler(u8 *object, s32 callback_arg);

void initialize_item_menu_request_state(void *state, s32 base_value);


s32 count_town_items(void);
void fill_ten_paged_output_slots(s32 **outputs, s32 *page_info, s32 record_table);

struct ItemMenuPart;
struct ItemMenuObject;
void item_menu_no_op(struct ItemMenuPart **parts, struct ItemMenuObject *object);

#include "town/shop/storage_menu.h"

typedef struct ShopEmbeddedDataObject {
    u8 pad_00[0x1C];
    s32 flags_1C;
    u8 embedded_stream_storage[0xA0];
    void *subrecord_data;
    u8 pad_C4[0x8];
    void *embedded_data;
} ShopEmbeddedDataObject;

typedef struct ShopRecordResetObject {
    u8 pad_00[0x8];
    s32 ramp_step;
    u8 inline_state_storage[0x90];
    void *step_resources;
    u8 pad_A0[0x8];
    void *record_resources;
} ShopRecordResetObject;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 is_unk_18_n_12_unk_1_a_between_n_37_n_41(void);

void * create_item_menu_object(s32 selector);

s32 advance_shop_entry_index_107(s32 index);
s32 count_free_item_slots(void);

#include "shared/entity.h"
struct S_800AE30C_0;
struct S_800B2D00_0;
struct S_800B61C0_1;
struct TownObject;
void advance_five_step_fixed_point_ramp(void *sub_object);
void *build_encoded_display_sequence(s32 source, u8 *outputBuffer);
void close_twin_shop(struct S_800AE30C_0 *shop);
void collect_selected_record_values(s32 *output, EntityRec *record);
s32 count_nonzero_fixed_table_words(void);
void ease_rgb_to_neutral_gray(u8 *object);
void fill_display_slots(EntityRec *source, s32 output);
void fill_ten_paged_entry_slots(s32 **outputs, struct S_800B2D00_0 *page_info, s32 entries_base);
s32 find_target_byte_index_in_list(void);
u32 find_unused_pool_slot(s32 *used_addrs, s32 pool_index, s32 slot_count);
s32 get_first_free_four_byte_entry_index_n_1_none_available(void *entry, s32 entry_count);
s32 get_mode_selected_value(void);
void handle_grid_menu_input(GridMenuObject *menu);
void handle_twin_shop_input(s32 *menu);
void pass_indexed_entry_address(GridMenuObject *entry_table);
void populate_display_row(struct S_800B61C0_1 *entry, s32 widgets_base, s32 row);
void populate_display_row_with_icon(void *entry_data, s32 display_base, s32 row_index);
void process_shop_embedded_data(ShopEmbeddedDataObject *record);
s32 select_choice_from_input_flags(s32 *choice_values);
void set_shop_slot_colors(struct TownObject *object, s32 index);
void set_shop_subrecord_values(s32 record_address, s32 value_10, s32 value_08);
void store_record_check_result(void *record);
void store_shop_embedded_value(s32 base_addr, s32 value);

#include "records/Rec_func_800B15B8_arg0.h"
struct ItemMenuTransition;
void animate_item_menu_cursor_transition(struct ItemMenuTransition *state);
s32 check_shop_entry_type_and_flags(void *entry);
s32 count_nonzero_entries(s32 *entries);
void finish_item_menu_child_and_release_list(void *record);
void reset_five_shop_slots(Rec_func_800B15B8_arg0 *owner);
void update_current_shop_page(void *list);

struct Obj_800B45A0;
void advance_inner_value_and_complete(struct Obj_800B45A0 *obj);
void apply_linked_record_defaults(void *record);

struct MotionVector;
struct S_8009ECF0_0;
struct TownActor;
void move_toward_target_check_completion_countdown_expires(struct TownActor *actor, s32 context, struct MotionVector *motion, s32 extra);
void run_both_updates_decrement_countdown_check_completion(struct S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx);

void advance_item_menu_object_animation(struct ItemMenuTransition *object);
s8 *clear_bytes(s8 *buffer, s32 length);
void copy_a_pointer_table_initializes_extra_data_tag_hex_13(s32 entry_index, void *source);
void format_and_display_entity_stats(void *stats, void *panels);
void initialize_storage_cursor(struct StorageOwner *object);
void initialize_storage_display_links(struct StorageDisplayLinks *state, union StorageDisplayBlock *primary, union StorageVector *secondary);
void *link_shop_nodes_in_configured_order(void *node_table);
void populate_display_rows(s32 source_id, void *display);
s32 select_a_town_entry_writes_root_relative_coordinates_output(s32 entryIndex);
void set_storage_entry_text(struct StorageEntry *entry, s32 text, s32 style, s16 x, s32 y);
void store_table_index_and_entry_bytes(void *object, s32 index);
void update_storage_display(struct StorageOwner *object);

#endif
