#ifndef TOWN_SCENE_H
#define TOWN_SCENE_H

#include "common.h"


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
void process_entry_with_exit_flag(struct Rec_func_800165F4_arg0 *, s32);

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

#endif
