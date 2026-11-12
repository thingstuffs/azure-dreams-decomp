#ifndef TOWN_H
#define TOWN_H
struct ObjectPosition;
struct SpriteFrameState;

#include "common.h"


/* func_806D6800.c */
s32 town_table_contains_first_byte_d(s32 target_value);

/* Callback entry points. */
void fade_effect_and_mark_cleanup(void *record, s32 unused, struct SpriteFrameState *effect);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *set_item_w0(s8 item_byte_0, s8 item_byte_1, s8 item_byte_2, s8 item_byte_3);

#include "shared/town_object.h"
void init_flagged_entity_action(TownObjectRecord *record, void *unused, void *handler_context);
void init_threshold_countdown_action(TownObjectRecord *record, void *unused, void *handler_context);
void init_timed_dispatch_action(TownObjectRecord *record, void *unused, void *handler_context);
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void initialize_action_object_type_six(TownObjectRecord *record, void *ptr, void *ptr2);
void initialize_action_object_with_counter(TownObjectRecord *record, struct ObjectPosition *unused, s32 setup_value);
s32 input_angle_with_offset(s32 unused, s32 angle_offset);

void init_sound_threshold_action(s32 **record, struct ObjectPosition *unused, s32 setup_value);


void init_height_interpolation_action(TownObjectRecord *record, void *unused, void *handler_context);

void forward_context_request_to_handler_b(void *context, s32 request);
void forward_context_request_to_handler_c(void *context, s32 request);
s32 forward_context_request_to_handler_d(void *context, s32 request);
void forward_context_request_to_handler_e(void *context, s32 request);
void forward_context_request_to_handler_f(void *context, s32 request);
void forward_context_request_to_handler_g(void *context, s32 request);
void set_scene_entry_flag_k(void);
void initialize_entity_handlers_and_position(s32 entity_id, s32 x, s32 y);
struct TownTimedTransitionState;
void update_timed_state_transition(struct TownTimedTransitionState *state);

#include "shared/item_menu.h"
struct S_800B3178_0;
void call_the_same_context_both_processing_routines(s32 value, s32 context);
void populate_paged_entries_with_brightness(void **entries, struct S_800B3178_0 *page_info, s32 source_table);
void position_decimal_digit_parts(ItemMenuObject *object);
void remove_selected_entry_from_list(s32 list_addr, s32 index);
void run_entry_update_steps(s32 entry_id);

void apply_upper_lower_boundary_adjustments_fixed_point(s32 context, s32 *value);
void clear_indexed_table_flag(void *record);
s32 directional_buttons_to_angle(s32 buttons);
void dispatch_item_menu_request_result(void *request);
s32 func_8001673C(s32 grid_y, s32 grid_x);
s32 func_800B0198(ItemMenuObject *object, s32 entry_count);
void handle_object_bounds_and_cleanup(TownObjectRecord *object, void *check_data, void *fallback_data);
s32 load_item_menu_display_resource(void *object, s32 resource_id);
s16 *map_cell_address_at_tile(s32 tile_x, s32 tile_y);
void send_item_menu_page_entries_to_formatter(s32 entryTableAddress, s32 entryCount);
void set_paired_entry_brightness(void *object);
void set_resident_flag_when_item_present(u16 *record);
void sort_selected_record_entries(void *record);
s16 *town_map_mod_read_p(s16 world_x, s16 world_y);
void update_the_data_set_local_global_flags(void *object, void *update_data);

void *initialize_packed_record_defaults(void *record);

s32 town_table_contains_first_byte_b(s32 target_value);

void update_actor_movement_with_radial_effects(s32 object_id, ObjectPosition *object, s32 update_context);

#endif
