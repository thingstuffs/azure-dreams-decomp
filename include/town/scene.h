#ifndef TOWN_SCENE_H
#define TOWN_SCENE_H

#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"


/* dispatch_inputs_by_current_state.c */
s32 dispatch_inputs_by_current_state(s32 input_a, s32 input_b, s32 input_c, s32 input_d);

/* process_town_records.c */
void process_town_records(s32 records_addr, s32 record_count);


/* select_data_for_requested_kind.c */
void *select_data_for_requested_kind(s32 lookup_id, s32 lookup_index, s32 data_kind);

/* dispatch_first_rejected_entry_b.c */
s32 dispatch_first_rejected_entry_b(void);

/* is_next_entry_zero_after_skipping.c */
s32 is_next_entry_zero_after_skipping(s32 list_index);


/* check_progress_against_callback.c */
s32 check_progress_against_callback(void);


/* get_record_value_tier.c */
s32 get_record_value_tier(void);

void *resolve_event_response_key(s32 unused_a, void *unused_b, s32 key);
void *dispatch_event_request(s32 request, void *data, s32 mode);

void *select_first_or_later_use_value(s32 unused_0, s32 unused_1, s32 selector);
void *return_zero_event_value(s32 unused);
extern void *D_800166F8[];
extern void *D_80016718[];

s32 forward_request_if_ready(void *request_value);
s32 pass_and_clear_selected_entry_byte(void *context, s32 entry_index);

s32 apply_scene_override_flag(s32 unused_first, s32 unused_second);
s32 check_any_entry_matches_predicate(void);
s32 lookup_variant_with_special_overrides(s32 requiredFlag, s32 completionFlag);
s32 *select_state_result_with_lookup_overrides(s32 first_value, s32 second_value, s32 unused_context);

void run_events_5a5_5c2_and_reset(void);
s32 increment_and_check_three(void);

s32 check_counter_threshold(void);
void subtract_threshold_from_counter(void);

void request_handler_state_9(void);
void request_handler_command_17(void);

s32 set_indexed_entry_flag_if_dac(void *object, s32 entry_index);

struct Rec_func_800165F4_arg0;
s32 process_entry_with_script_flag(struct Rec_func_800165F4_arg0 *object, s32 entry_index);

/* Map-exit callback invoked by change_map. */
struct RuntimeState;
void reserve_town_monster_load_two(struct RuntimeState *unused_transition, void *unused_map_data);

/* Complete TOWN callbacks at the validated phase load addresses. */
s32 process_entry_linked_nonzero(void *object, s32 entry_index);
s32 process_entry_linked_five(void *object, s32 entry_index);
s32 set_entry_flag_if_5c7(void *object, s32 entry_index);
void set_script_flag_94c(void);
void start_keima_and_clear_flag(void);
void set_active_entry_script_flag(void);
void mark_active_entry_script_flag(void);
s32 process_checked_scene_entry(void *object, s32 entry_index);
s32 process_checked_entry_flags(void *object, s32 entry_index);
void set_indexed_scene_entry_flag(void *object, s32 entry_index);
extern u8 D_8001798C[];
extern u8 *D_80017AA4;

struct Rec_func_800165F4_arg0;
s32 process_entry_with_exit_flag(struct Rec_func_800165F4_arg0 *, s32);

/* Signed scene-position deltas. */
struct S_80019DE0_0;
void apply_signed_stat_deltas(void *stat_deltas);
void apply_half_step_position_deltas(struct S_80019DE0_0 *deltas);
void apply_position_offset_pair(void *offsets);
/* Index-returning flag-table dispatchers. */
s32 call_indexed_callback_failed_test(void);
s32 dispatch_first_failed_entry_b(void);

/* The two fixed RAM buffers used by scene image transfers. */
typedef struct { s16 x, y, w, h; } SceneImageRect;
#define SCENE_IMAGE_BUFFER_0 ((u32 *)0x80020000)
#define SCENE_IMAGE_BUFFER_1 ((u32 *)0x80024000)
void store_scene_image_pair(void);

/* Calls the scene service at +0x258 with value one. */
void call_scene_service_one(void);

/* Return the selected scene text, including flag-selected alternatives. */
char *resolve_scene_entry_text(void *context, s32 unused, s32 selection);

/* Return the stored state byte as the word consumed by scene tests. */
s32 get_state_record_byte(void);

/* Callback entry points. */
s32 *get_data_pointer_1691_c(void);
void update_slot_machine(void *machine, void *position);

/* Square-scene choice records. Consumers index 16-byte entries, call the
 * predicate at +0, call the text selector at +4, and read the flag at +12. */
typedef Rec_func_800165F4_arg0 SquareSceneEntry;
typedef s32 (*TownChoicePredicate)(SquareSceneEntry *, s32);
typedef void *(*TownChoiceText)(SquareSceneEntry *, s32, s32);
typedef u8 *TownChoiceData;
typedef struct {
    TownChoicePredicate predicate;
    TownChoiceText text;
    TownChoiceData value;
    s16 script_flag;
    s16 reserved;
} TownSceneChoice;
s32 apply_gate_5217_entry(SquareSceneEntry *entry, s32 entry_index);
s32 apply_gate_5000_entry(SquareSceneEntry *entry, s32 entry_index);
s32 apply_gate_5000_flag_entry(SquareSceneEntry *entry, s32 entry_index);
s32 apply_gate_5211_flag_entry(SquareSceneEntry *entry, s32 entry_index);
s32 apply_gate_5003_flag_entry(SquareSceneEntry *entry, s32 entry_index);
void *select_square_entry_or_fallback(SquareSceneEntry *entry, s32 entry_index, s32 selection);
void *select_square_entry_or_alternate(SquareSceneEntry *entry, s32 entry_index, s32 selection);
s32 flag_entry_if_record_eleven(SquareSceneEntry *entry, s32 entry_index);
extern TownSceneChoice square_gate_choices[4];
extern TownSceneChoice square_progress_choices[6];
extern TownSceneChoice square_flag_choices[17];
extern TownSceneChoice square_record_choices[4];


/* A terminal scene choice accepts unconditionally and has an argument-free
 * action. The layout is the ordinary 16-byte scene choice record. */
typedef s32 (*TownTerminalPredicate)(void);
typedef s32 (*TownTerminalAction)(void);
typedef u8 *TownTerminalData;
typedef struct {
    TownTerminalPredicate predicate;
    TownTerminalAction action;
    TownTerminalData value;
    s16 script_flag;
    s16 reserved;
} TownTerminalChoice;

/* Street-event opcode 0x4C callbacks. */
void set_script_flag_db3(void);
void clear_script_flag_db3(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
#include "records/Rec_D_800FE490.h"
struct FallingObjectState;
void func_800C8D34(struct FallingObjectState *object, void *context, void *sprite);
void initialize_the_store_two_values_set_state_flags(Rec_D_800FE490 *record, s32 value_08, s32 value_0c);

struct Node;
struct Node *handle_finds_first_eligible_active_node_in_circular_list(struct Node *origin);

s32 count_listed_enabled_records(void);

void advance_dispatch_state_to_two(void);
s32 advance_to_next_enabled_entry(void);
s32 apply_selected_entry_values(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 check_callback_record_bytes(s32 expected_second, s32 expected_first);
s32 count_enabled_town_entries(void);
s32 find_first_enabled_entry_id(void);
s32 *get_special_data_for_low_value_id(s32 id);
s32 process_checked_entry(void *object, s32 entryIndex);
s32 select_status_code_from_callback(void);

void dispatch_paired_table_values(void);
void process_flagged_type_0x18_entries(void);

struct S_func_8001A854_4;
s32 blend_point_2s_by_signed_weight(void *base_point, void *other_point, s32 blend_weight, s32 other_weight, void *result_point);
void call_state_handler_and_copy_values(struct S_func_8001A854_4 *output, s32 handler_arg);

void copy_words_backward_from_offset(s32 dest_addr, s32 src_addr, s32 byte_count);

struct S_8001A188_0;
struct S_8001A188_1;
void *build_entry_list(s32 entry_index);
u8 *build_selected_entry_output(s32 selected_index);
s32 build_three_value_block(void);
void configure_the_set_mode_n_3(void *record, void *position, void *bounds);
void copy_town_record_pair_fields(struct S_8001A188_0 *dest, struct S_8001A188_1 *src);
void copy_words(s32 *dst, s32 *src, s32 count);
s32 *find_entry_by_paired_key(s32 *entries, s32 key);
s32 find_entry_index_by_grid_bytes(s32 match_byte_1, s32 match_byte_0);
u8 *get_special_data_by_id(s32 id);
s32 has_matching_entry_result(s32 first_value, s32 second_value);
void invoke_match_callback_or_lookup(void);
s32 *lookup_with_override_fallback(void *key, s32 unused, s32 context);
void post_code_0x107_when_slot_ready(s32 group, s32 slot);
s32 prepare_stored_value_pair(void);
void print_scene_sequence_number_sno(s32 kind);
void process_flagged_entries_follow_four(u8 *entries);
void run_setup_and_remap_mode_records(s32 table_index, s32 mode);
s32 try_decrement_state_counter(s32 grid_y, s32 grid_x);

u8 *select_town_byte_array(void);

void configure_the_set_mode_n_1(void *record, void *position, void *bounds);

#include "shared/entity.h"
s32 advance_counter_modulo_eight(void);
void advance_town_events_and_dispatch_entry(void);
void apply_record_value_when_enabled(Rec_func_800165F4_arg0 *record, s32 handler_context);
s32 blit_default_rectangle(void);
s32 call_helper_with_fixed_id_0x118a(void);
void configure_the_set_mode_n_4(void *record, void *position, void *bounds);
void dispatch_mode_two_by_state(s32 state_input);
s32 find_eligible_entry(void *context);
s32 get_helper_result(void);
s32 get_smaller_query_result_capped_hex_80_writes_associated_output(EntityRec *source, s32 *out_detail);
s32 low_12_values_within_511(s32 value_a, s32 value_b);
void pass_2(s32 dispatch_context, s32 unused, s32 dispatch_arg);
s32 process_request_and_notify(void *context, s32 request);
char *select_address_based_input(void);
void *select_data_for_condition_d_83(void);
void *select_data_pointer_based_result(void);
s32 *select_response_and_set_d_80(void);
void set_up_town_resolves_record(void);
void write_value_through_pointer(s32 *destination, s32 value);

#endif
