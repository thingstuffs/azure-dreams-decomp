#ifndef INCLUDE_TOWN_SCENE_ENTRY_REQUESTS_H
#define INCLUDE_TOWN_SCENE_ENTRY_REQUESTS_H

#include "common.h"
#include "town/scene/position_entries.h"

struct SceneFlagContext;

void apply_entry_keyed_values(struct ScenePositionEntry *entry_table, void *resource, s32 entry_key);
s32 process_current_cell_and_clear(void *object, s32 entry_index);
s32 update_entry_state_and_clear(void *object, s32 entry_index);
s32 load_entry_value_and_handle_followup(void *object, s32 entry_index);
void select_based_parameters(void *context, s32 entry_index);
void apply_naoruru_hospital_position(s32 callerValue, s32 unused, s32 callerData);
s32 *set_entry_flag_and_get_response(s32 first_input, s32 second_input);
s32 process_entry_unless_sbs22_pad28(void *handler_arg_a, s32 handler_arg_b);
s32 process_entry_if_pad28_set(void *handler_arg_a, s32 handler_arg_b);
s32 pass_entry_unless_pad29_set(void *slot_index, s32 slot_value);
s32 pass_entry_unless_pad28_set(void *slot_index, s32 slot_value);
s32 pass_entry_if_pad28_or_pad29(void *context, s32 entry_index);
void forward_to_process_checked_entry(void *context, s32 entry_index);
s32 process_entry_if_sbs22_pad29(void *context, s32 entryIndex);
void *dispatch_entry_by_799_flag(void);
s32 pass_or_process_entry(void *context, s32 entry_index);
s32 mark_entry_and_process_if_sbs22_pad28(void *primaryInput, s32 secondaryInput);
s32 snap_player_beside_actor(void);
void select_handler_by_state_code_0x798(s32 slotIndex);
void forward_context_value_to_handler_d(void *first_arg, s32 second_arg);
void forward_context_value_to_handler_a(void *input_a, s32 input_b);
void forward_context_value_to_handler_b(void *first_value, s32 second_value);
void forward_context_value_to_handler_c(void *context, s32 value);
void forward_context_value_to_handler_e(void *first_input, s32 second_input);
void apply_signed_value_to_indexed_entry(void *object, s32 index);
u8 *build_town_event_records(void *unused);
s32 record_checked_entry_result(void *check_input_1, s32 check_input_2);
struct S_8046C8C4_0;
void set_flag_from_indexed_entry(struct S_8046C8C4_0 *table, s32 entry_index);

s32 process_checked_entry(void *object, s32 entry_index);
s32 func_80019928(void *object, s32 entry_index);
s32 process_entry_or_start_message(void *object, s32 entry_index);
s32 process_entry_set_pad36_on_failure(void *object, s32 entry_index);

s32 *run_scene_helper_and_get_result(void);
s32 dispatch_scene_entry_value(s32 entry_id, s32 unused, s32 value);
s32 dispatch_scene_alt_tables(void *request, s32 unused, s32 mode);
s32 dispatch_scene_request_with_fixed_data(s32 request, s32 unused, s32 value);
u8 *get_shared_scene_result(void);
void *lookup_scene_entry_with_kind_overrides(s32 key, s32 unused, s32 kind);
struct Rec_func_800165F4_arg0;
s32 apply_scene_entry_values(struct Rec_func_800165F4_arg0 *entry, s32 entry_index);
void apply_scene_record_value(void *context, s32 unused, s32 lookup_key);
s32 lookup_entry_value_and_set_flag(struct ScenePositionEntry *entries, struct SceneFlagContext *context, s32 lookup_key);
s32 lookup_entry_and_apply_record_code(void *table, void *context, s32 lookup_key);
void dispatch_scene_entry_table(void);
void dispatch_scene_request_with_local_words(s32 request, s32 unused, s32 value);
void forward_scene_entry_index_a(void *object, s32 entry_index);
void forward_scene_entry_index_b(void *object, s32 entry_index);
void forward_scene_entry_index_c(void *object, s32 entry_index);
s32 forward_scene_request_arguments(struct Rec_func_800165F4_arg0 *entry, s32 entry_index);
void process_entry_when_table_has_seven(s32 target, s32 value);
void store_scene_value_pair(s32 first_value, s32 second_value);
s32 store_pair_and_process_entry(struct Rec_func_800165F4_arg0 *row, s32 entry_index);

struct SceneActionEntry;
s32 dispatch_first(s32 dispatch_value, s32 unused, s32 dispatch_option);
s32 store_pair_and_test_entry_flags(struct SceneActionEntry *entry, s32 value);

void *lookup_keima_entry(void *context, s32 unused, s32 code);

void release_lshop_entry_and_compact(s32 slot_index);

s32 all_entries_pass_check(s16 *values);

/* Set the current town scene entry state byte to 3. */
void set_selected_entry_state_3(void);

#endif
