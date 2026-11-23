#ifndef TOWN_H
#define TOWN_H
struct ObjectPosition;
struct SpriteFrameState;
struct TownObjectSet;

#include "common.h"


/* func_806D6800.c */
s32 town_table_contains_first_byte_d(s32 target_value);

/* Callback entry points. */
void fade_effect_and_mark_cleanup(void *record, s32 unused, struct SpriteFrameState *effect);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *set_item_w0(s8 item_byte_0, s8 item_byte_1, s8 item_byte_2, s8 item_byte_3);

#include "shared/town_object.h"
void init_flagged_entity_action(TownObjectRecord *record, struct ObjectPosition *unused, struct SpriteFrameState *handler_context);
void init_threshold_countdown_action(TownObjectRecord *record, struct ObjectPosition *unused, void *handler_context);
void init_timed_dispatch_action(TownObjectRecord *record, struct ObjectPosition *unused_position, void *handler_context);
void initialize_action_object(s32 **record, struct ObjectPosition *ptr, void *ptr2);
void initialize_action_object_type_six(TownObjectRecord *record, void *ptr, void *ptr2);
void initialize_action_object_with_counter(TownObjectRecord *record, struct ObjectPosition *unused, struct SpriteFrameState *sprite);
s32 input_angle_with_offset(s32 unused, s32 angle_offset);

void init_sound_threshold_action(s32 **record, struct ObjectPosition *unused, s32 setup_value);


void init_height_interpolation_action(TownObjectRecord *record, struct ObjectPosition *unused, void *handler_context);

s32 forward_context_request_to_handler_b(struct TownObjectSet *entry, s32 entry_index);
s32 forward_context_request_to_handler_c(struct TownObjectSet *entry, s32 entry_index);
s32 forward_context_request_to_handler_d(struct TownObjectSet *entry, s32 entry_index);
s32 forward_context_request_to_handler_e(struct TownObjectSet *entry, s32 entry_index);
s32 forward_context_request_to_handler_f(struct TownObjectSet *entry, s32 entry_index);
s32 forward_context_request_to_handler_g(struct TownObjectSet *entry, s32 entry_index);
void set_scene_entry_flag_k(void);
void initialize_entity_handlers_and_position(s32 entity_id, s32 x, s32 y);
void update_timed_state_transition(TownObjectRecord *state);

#include "shared/item_menu.h"
struct StoragePage;
struct DungeonItemEntry;
struct ColliderView;
void apply_bound_adjustments(struct ColliderView *collider, ObjectPosition *position);
void populate_paged_entries_with_brightness(ItemMenuPart **entries, struct StoragePage *page_info, struct DungeonItemEntry **source_table);
void place_item_menu_cursor_parts(ItemMenuObject *object);
struct DungeonItemEntry;
void remove_selected_entry_from_list(struct DungeonItemEntry **list, s32 index);
void update_entry_resources_and_brightness(s32 entry_id);

void start_adjustment_at_value_bounds(struct ColliderView *collider, ObjectPosition *position);
void clear_indexed_table_flag(struct DungeonItemEntry *record);
s32 directional_buttons_to_angle(s32 buttons);
void dispatch_item_menu_request_result(void *request);
s32 func_8001673C(s32 grid_y, s32 grid_x);
s32 func_800B0198(ItemMenuObject *object, s32 entry_count);
void retire_object_or_animate_sprite(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite);
struct ItemMenuTransition;
s32 load_item_menu_display_resource(struct ItemMenuTransition *object, s32 resource_id);
s16 *map_cell_address_at_tile(s32 tile_x, s32 tile_y);
struct ItemMenuPart;
void remove_item_menu_entry_objects(struct ItemMenuPart **entries, s32 entryCount);
void set_paired_entry_brightness(void *object);
void set_ultima_egg_pickup_flag(u16 *record);
struct ItemMenuInputObject;
void sort_selected_record_entries(struct ItemMenuInputObject *record);
s16 *town_map_mod_read_p(s16 world_x, s16 world_y);
void remove_object_with_item_data(void *object, void *update_data);

void *init_scene_entry_table_defaults(void *record);

s32 town_pair_table_has_first(s32 target_value);

void update_actor_movement_with_radial_effects(s32 object_id, ObjectPosition *object, s32 update_context);

#endif
