#ifndef TOWN_SHOP_H
#define TOWN_SHOP_H
#include "shared/dungeon_item_entries.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
struct ActorRecord;
struct ColliderView;

#include "common.h"

#include "town/shop/grid_menu.h"
#include "town/shop/storage_menu.h"
#include "shared/item_menu.h"

/* get_player_homerank.c */
s32 get_player_homerank(void);

s32 dispatch_item_menu_entry_callback(ItemMenuTransition *state, s32 callback_arg);
s32 invoke_item_menu_object_callback(ObjectNodeHeader *object, s32 callback_arg);

void initialize_item_menu_request_state(ItemMenuObject *object, ItemMenuStateNode *owner);

s32 count_town_items(void);
void fill_ten_paged_output_slots(void *part_table, StoragePage *page_info, DungeonItemEntry **record_table);

struct ItemMenuPart;
struct ItemMenuObject;
void item_menu_no_op(struct ItemMenuPart **parts, struct ItemMenuObject *object);


typedef struct ShopEmbeddedDataObject {
    u8 pad_00[0x1C];
    s32 flags_1C;
    u8 embedded_stream_storage[0xA0];
    void *subrecord_data;
    u8 pad_C4[0x8];
    void *embedded_data;
} ShopEmbeddedDataObject;

typedef struct ShopRecordResetObject {
    void *owner_body;
    u8 pad_04[4];
    s32 ramp_step;
    u8 pad_0C[0xC];
    ObjectNodeHeader *owner_node;
    FrameState stream_state;
    u8 pad_28[0x74];
    ItemMenuDisplayBlock *step_resources;
    u8 pad_A0[8];
    ItemMenuPart **record_resources;
} ShopRecordResetObject;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
s32 is_map_state_in_special_range(void);

void * create_item_menu_object(s32 selector);

s32 advance_shop_entry_index_107(s32 index);
s32 count_free_item_slots(void);

#include "shared/entity.h"
struct TownObject;
void advance_five_step_fixed_point_ramp(void *sub_object);
void *build_encoded_display_sequence(s32 source, u8 *outputBuffer);
void collect_selected_record_values(s32 *output, ActorRecord *record);
void close_twin_shop(ObjectNodeHeader *shop);
s32 count_town_items_at_fixed_table(void);
void ease_rgb_to_neutral_gray(u8 *object);
void fill_display_slots(ActorRecord *source, ItemMenuPart **output);
s32 find_target_index_in_list(void);
DungeonItemEntry *find_unused_pool_slot(DungeonItemEntry **used_addrs, s32 pool_index, s32 slot_count);
s32 find_free_entry_index(void *entry, s32 entry_count);
s32 get_mode_selected_value(void);
void handle_grid_menu_input(GridMenuObject *menu);
void handle_twin_shop_input(GridMenuObject *menu);
void refresh_selected_item_name_with_fallback(GridMenuObject *entry_table);
void populate_display_row(DungeonItemEntry *entry, ItemMenuPart **parts, s32 row);
void populate_action_display_row(void *entry_data, ItemMenuPart **parts, s32 row_index);
void fade_shop_change_indicators(ShopEmbeddedDataObject *record);
s32 select_choice_from_input_flags(s32 *choice_values);
void set_shop_slot_colors(struct TownObject *object, s32 index);
void set_shop_page_and_selection(struct ObjectNodeHeader *node, s32 value_10, s32 value_08);
void set_status_from_flagged_total(GridMenuObject *record);
void set_shop_selected_entry(struct ObjectNodeHeader *node, s32 value);

#include "records/Rec_func_800B15B8_arg0.h"
struct ItemMenuTransition;
void animate_item_menu_cursor_transition(struct ItemMenuTransition *state);
s32 check_shop_entry_type_and_flags(DungeonItemEntry *entry);
s32 count_nonzero_entries(DungeonItemEntry **entries);
struct S_800B05DC_0;
void release_item_menu_display(struct S_800B05DC_0 *record);
void reset_five_shop_slots(Rec_func_800B15B8_arg0 *owner);
struct ShopWindow;
void update_current_shop_page(struct ShopWindow *list);

struct Obj_800B45A0;
void ease_value_and_remove_node(struct Obj_800B45A0 *obj);
void apply_linked_record_defaults(AlternateStorageOwner *record);

struct MotionVector;
struct ObjectPosition;
struct S_8009ECF0_0;
struct TownActor;
struct TownObjectRecord;
struct SpriteFrameState;
void move_toward_view_reference(struct TownObjectRecord *actor, void *context, struct ObjectPosition *motion, struct SpriteFrameState *extra);
void update_entity_until_countdown_ends(struct S_8009ECF0_0 *state, struct ColliderView *update_ctx, struct ObjectPosition *position, s32 finish_ctx);

void advance_item_menu_object_animation(struct ItemMenuTransition *object);
s8 *clear_bytes(s8 *buffer, s32 length);
void install_slot_record_with_extra_data(s32 entry_index, void *source);
void format_and_display_entity_stats(struct ActorRecord *stats, ItemMenuPart **panels);
void initialize_storage_cursor(struct StorageOwner *object);
void initialize_storage_display_links(struct ItemMenuDisplayLinks *state, union StorageDisplayBlock *primary, ItemMenuDisplayPosition *secondary);
void *link_shop_nodes_in_configured_order(void *node_table);
void populate_display_rows(struct ActorRecord *actor, ItemMenuPart **display);
s32 set_shop_target_to_entry(s32 entryIndex);
void set_storage_entry_text(ItemMenuPart *entry, char *text, s32 style, s16 x, s32 y);
struct ItemMenuInputObject;
void store_shop_display_preset(struct ItemMenuInputObject *object, s32 index);
void update_storage_display(struct StorageOwner *object);
void position_decimal_digits_node(ObjectNodeHeader *node);
void set_alternate_menu_node_coordinates(ObjectNodeHeader *node);

struct ShopMenu;
struct ItemMenuInputObject;
void close_item_move_menu(struct ItemMenuInputObject *record);
void setup_shop_window(void *object, ObjectNodeHeader *owner, s32 setup_value_2, s32 setup_value_3, s32 setup_value_4, s32 setup_value_5, DungeonItemEntry *items, s32 setup_value_7);
s32 get_mode_value_or_default(s32 mode);
void close_shop(struct ShopMenu *shop);
void fade_menu_side_indicators(struct ShopRecordResetObject *object);

void decrement_entry_and_notify_handlers(struct ItemMenuInputObject *state);
s32 move_item_to_list(struct ItemMenuInputObject *state);
void apply_input_choice_value(s32 entry_id);
void update_active_entry_and_notify_handlers(struct ItemMenuInputObject *state, s32 input);

void *format_compared_stat_pairs(void *text, ActorRecord *stats);

u8 *build_shop_goods_entries(u8 *entries);

struct TownEventRegistrationHandle;
extern struct TownEventRegistrationHandle *shop_scene_registration_handle;

extern u8 shop_scene_entry_bytes[];

struct TownEventRegistrationHandle *register_shop_goods_entries(void);

#endif
