#ifndef INCLUDE_TOWN_SCENE_ENTRY_REQUESTS_H
#define INCLUDE_TOWN_SCENE_ENTRY_REQUESTS_H

#include "common.h"
#include "town/scene/position_entries.h"

void apply_entry_keyed_values(s16 *entry_table, void *resource, s32 entry_key);
s32 resolve_entry_flag(u8 *entry_table, void *context, s32 entry_key);
s32 process_current_cell_and_clear(void *object, s32 entry_index);
s32 update_entry_state_and_clear(void *object, s32 entry_index);
s32 load_entry_value_and_handle_followup(void *object, s32 entry_index);
void select_based_parameters(void *context, s32 entry_index);
s32 dispatch_by_state_code_0x798(void *handler_arg_a, s32 handler_arg_b);
s32 dispatch_entry_by_798_state(void *handler_arg_a, s32 handler_arg_b);
s32 dispatch_by_state_code_0x799(void *slot_index, s32 slot_value);
s32 dispatch_menu_pair_by_798_state(void *slot_index, s32 slot_value);
s32 dispatch_entry_and_set_11_fb_when_flagged(void *context, s32 entry_index);
void call_clear_script_flag_bit(void *context, s32 entry_index);
s32 dispatch_entry_by_799_flag(void *context, s32 entryIndex);
s32 dispatch_entry_by_798_and_799_flags(void *context, s32 entry_index);
s32 select_handler_by_state_code_0x798(void *primaryInput, s32 secondaryInput);
void forward_context_value_to_handler_d(void *first_arg, s32 second_arg);
void forward_context_value_to_handler_a(void *input_a, s32 input_b);
void forward_context_value_to_handler_b(void *first_value, s32 second_value);
void forward_context_value_to_handler_c(void *context, s32 value);
void forward_context_value_to_handler_e(void *first_input, s32 second_input);
void apply_signed_value_to_indexed_entry(void *object, s32 index);
s32 record_check_returned(void *check_input_1, s32 check_input_2);
struct S_8046C8C4_0;
void pass_indexed_entry(struct S_8046C8C4_0 *table, s32 entry_index);

s32 process_checked_entry(void *object, s32 entry_index);
s32 func_80019928(void *object, s32 entry_index);
s32 wait_for_dialogue_then_close(void *object, s32 entry_index);
s32 dispatch_code_7_a_0_by_status(void *object, s32 entry_index);

s32 *run_scene_helper_and_get_result(void);
s32 dispatch_scene_entry_value(s32 entry_id, s32 unused, s32 value);
s32 dispatch_scene_alt_tables(void *request, s32 unused, s32 mode);
s32 dispatch_scene_request_with_fixed_data(s32 request, s32 unused, s32 value);
s32 dispatch_scene_request_with_tables(s32 request, s32 unused, s32 value);
s32 lookup_scene_entry_with_checked_fallback(s32 context, s32 check_value, s32 selector);
u8 *get_shared_scene_result(void);
void *lookup_scene_entry_with_kind_overrides(s32 key, s32 unused, s32 kind);
void apply_scene_entry_values(void *data, s32 value);
void apply_scene_record_value(void *context, s32 unused, s32 lookup_key);
s32 lookup_entry_apply_record_code(void *table, void *context, s32 lookup_key);
s32 lookup_entry_and_apply_record_code(void *table, void *context, s32 lookup_key);
void dispatch_scene_entry_table(void);
void dispatch_scene_request_with_local_words(s32 request, s32 unused, s32 value);
void forward_scene_entry_index_a(void *object, s32 entry_index);
void forward_scene_entry_index_b(void *object, s32 entry_index);
void forward_scene_entry_index_c(void *object, s32 entry_index);
void forward_scene_request_arguments(s32 input_a, s32 input_b, s32 input_c, s32 input_d);
void run_value_handler_after_flag_check(s32 target, s32 value);
void store_scene_value_pair(s32 first_value, s32 second_value);
void store_scene_values_after_flag_check(s32 value, s32 data);

struct SceneActionEntry;
s32 dispatch_first(struct SceneActionEntry *entry, s32 value);
s32 update_scene_and_select_action(struct SceneActionEntry *object, s32 value);
s32 initialize_scene_action_state(struct SceneActionEntry *object, s32 value);

void *lookup_keima_entry(void *context, s32 unused, s32 code);

void apply_four_values_and_refresh(s32 slot_index);

#endif
