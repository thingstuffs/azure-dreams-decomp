#ifndef TOWN_SCENE_EVENT_H
#define TOWN_SCENE_EVENT_H

#include "common.h"

struct Rec_func_800165F4_arg0;

s32 get_script_flag_tt_pad81(void);
s32 get_script_flag_sbs14_pad22(void);
s32 get_script_flag_sbs20_pad07(void);
s32 invoke_callback_event_11(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
u8 *select_event_data_table(s32 unused, s32 selector);

void initialize_active_event_data(void);

s32 check_event_value_in_list(s32 target_value);
s32 forward_context_request_to_handler(struct Rec_func_800165F4_arg0 *entry, s32 entry_index);
s32 forward_context_request_to_handler_c_68(struct Rec_func_800165F4_arg0 *entry, s32 entry_index);
void select_response_setting_niko_and_gosh(void *dispatch_value, s32 unused, s32 dispatch_context);
void *select_sero_end_response(void *object, s32 unused, s32 eventCode);
void set_ending_event_state(void);

s32 *clear_event_resource_state_and_get_buffer(s32 unused_selected_entry);
void set_script_flag_sbs14_pad22(void);
u8 *get_event_data_pointer(void);

void forward_stored_pair(void);
void clear_script_flag_sbs14_pad02(void);

s32 query_priority_event_state(void);

s32 *advance_event_state_and_get_resource(void);
u8 *reset_event_entry_and_get_resource(void);
#endif
