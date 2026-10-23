#ifndef TOWN_SCENE_H
#define TOWN_SCENE_H

#include "common.h"


/* process_town_records.c */
void process_town_records(s32 records_addr, s32 record_count);


/* is_next_entry_zero_after_skipping.c */
s32 is_next_entry_zero_after_skipping(s32 list_index);


/* check_progress_against_callback.c */
s32 check_progress_against_callback(void);


/* get_record_value_tier.c */
s32 get_record_value_tier(void);

void *resolve_event_response_key(s32 unused_a, void *unused_b, s32 key);
void *dispatch_event_request(s32 request, void *data, s32 mode);

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

#endif
