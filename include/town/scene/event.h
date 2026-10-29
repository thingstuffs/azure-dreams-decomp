#ifndef TOWN_SCENE_EVENT_H
#define TOWN_SCENE_EVENT_H

#include "common.h"

s32 query_event_d_82(void);
s32 dispatch_event_63_a_through_194_d_8(void);
s32 initialize_event_position_state(void);
s32 invoke_callback_event_11(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
u8 *select_event_data_table(s32 unused, s32 selector);

void initialize_active_event_data(void);

s32 check_event_value_in_list(s32 target_value);
void forward_context_request_to_handler(void *context, s32 request);
void forward_context_request_to_handler_c_68(void *context, s32 request);
void process_event_145_c_and_dispatch(void *dispatch_value, s32 unused, s32 dispatch_context);
void *select_event_data_and_fallback(void *object, s32 unused, s32 eventCode);
void set_event_state_and_dispatch_a_2(void);

s32 *clear_event_resource_state_and_get_buffer(void);
void dispatch_event_63_a_through_193_e_0(void);
u8 *get_event_data_pointer(void);

#endif
