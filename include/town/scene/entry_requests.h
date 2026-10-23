#ifndef INCLUDE_TOWN_SCENE_ENTRY_REQUESTS_H
#define INCLUDE_TOWN_SCENE_ENTRY_REQUESTS_H

#include "common.h"

s32 *run_scene_helper_and_get_result(void);
s32 dispatch_scene_entry_value(s32 entry_id, s32 unused, s32 value);
s32 dispatch_scene_alt_tables(s32 request, s32 unused, s32 mode);
s32 dispatch_scene_request_with_fixed_data(s32 request, s32 unused, s32 value);
s32 dispatch_scene_request_with_tables(s32 request, s32 unused, s32 value);
s32 lookup_scene_entry_with_checked_fallback(s32 context, s32 check_value, s32 selector);
u8 *get_shared_scene_result(void);
void *lookup_scene_entry_with_kind_overrides(s32 key, s32 unused, s32 kind);
void apply_scene_entry_values(void *data, s32 value);
void apply_scene_record_value(s32 value);
void dispatch_scene_entry_table(void);
void dispatch_scene_request_with_local_words(s32 request, s32 unused, s32 value);
void forward_scene_entry_index_a(void *object, s32 entry_index);
void forward_scene_entry_index_b(void *object, s32 entry_index);
void forward_scene_entry_index_c(void *object, s32 entry_index);
void forward_scene_request_arguments(s32 input_a, s32 input_b, s32 input_c, s32 input_d);
void run_value_handler_after_flag_check(s32 target, s32 value);
void store_scene_value_pair(s32 first_value, s32 second_value);
void store_scene_values_after_flag_check(s32 value, s32 data);

#endif
