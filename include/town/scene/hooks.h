#ifndef TOWN_SCENE_HOOKS_H
#define TOWN_SCENE_HOOKS_H
/* Prototypes of the functions defined in src/town/scene/hooks/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* clear_script_flag_db3.c */
void clear_script_flag_db3(void);

/* forward_context_value_options.c */
void forward_context_value_options(s32 context, s32 value, s32 options);

/* forward_context_value_to_handler.c */
void forward_context_value_to_handler_d(void *first_arg, s32 second_arg);

/* forward_context_value_to_handler_a.c */
void forward_context_value_to_handler_a(void *input_a, s32 input_b);

/* forward_context_value_to_handler_b.c */
void forward_context_value_to_handler_b(void *first_value, s32 second_value);

/* forward_context_value_to_handler_c.c */
void forward_context_value_to_handler_c(void *context, s32 value);

/* forward_context_value_to_handler_e.c */
void forward_context_value_to_handler_e(void *first_input, s32 second_input);

/* forward_data_and_value.c */
void forward_data_and_value(void *data, s32 value);

/* forward_data_and_value_b.c */
void forward_data_and_value_b(void *data, s32 value);

/* forward_entry_index.c */
void forward_entry_index(void *context, s32 entry_index);

/* forward_indexed_table_value.c */
void forward_indexed_table_value(s32 index);

/* forward_pair_to_handler.c */
s32 forward_pair_to_handler(s32 object, s32 entry_index);

/* forward_pair_to_handler_b.c */
s32 forward_pair_to_handler_b(s32 object, s32 entry_index);

/* forward_request_if_ready.c */
s32 forward_request_if_ready(void *request_value);

/* forward_request_with_local_template.c */
void forward_request_with_local_template(s32 first_value, s32 unused, s32 second_value);

/* forward_request_with_local_words.c */
void dispatch_scene_request_with_local_words(s32 request, s32 unused, s32 value);
void lookup_scene_entry_with_checked_fallback(s32 request, s32 unused, s32 value);

/* forward_request_with_tables_d.c */
s32 dispatch_scene_alt_tables(void *request, s32 unused, s32 mode);
s32 dispatch_scene_request_with_tables(void *request, s32 unused, s32 mode);

/* forward_scene_inputs.c */
void forward_scene_inputs(s32 input_a, s32 input_b, s32 input_c, s32 input_d);

/* forward_selected_entry_to_callback.c */
void forward_selected_entry_to_callback(void);

/* forward_shared_data.c */
void forward_shared_data(void);

/* get_shared_entry_buffer.c */
s32 *get_shared_entry_buffer(void);

/* get_shared_entry_buffer_aa.c */
void *get_scene_shared_buffer_aa(void);

/* get_shared_entry_buffer_ab.c */
void *get_scene_shared_buffer_ab(void);

/* get_shared_entry_buffer_l.c */
void *get_shared_entry_buffer_l(void);

/* get_shared_entry_buffer_y.c */
void *get_shared_entry_buffer_y(void);

/* get_shared_threshold_value.c */
s32 get_shared_threshold_value(void);

/* increase_shared_byte_four_enter_state_eight.c */
void increase_shared_byte_by_four_and_enter_state_eight(void *controller);

/* is_pair_result_valid.c */
s32 is_pair_result_valid(s32 first_input, s32 second_input);

/* is_pair_result_valid_b.c */
s32 is_pair_result_valid_b(s32 grid_y, s32 grid_x);

/* no_op_callback.c */
void no_op_callback_d(void);

/* noop_at_ffc.c */
void noop_at_8008_ffc_0(void);

/* noop_hook_i.c */
void noop_hook_i(void);

/* noop_hook_j.c */
void noop_hook_j(void);

/* point_shared_buffer_at_data.c */
void func_800161DC(void);
void point_shared_buffer_at_data(void);

/* point_shared_buffer_at_data_e.c */
void point_shared_buffer_at_data_e(void);

/* refresh_shared_state.c */
void refresh_shared_state(void);

/* register_shared_data.c */
void register_shared_data(void);

/* request_entry_rescan.c */
void request_entry_rescan(void);

/* return_argument.c */
s32 return_argument(s32 value);

/* return_argument_b.c */
s32 return_argument_b(s32 value);

/* return_zero_fn.c */
s32 return_zero_fn(void);

/* return_zero_fn_p.c */
s32 return_zero_fn_p(void);

/* send_shared_town_record.c */
void send_shared_town_record(void);

/* set_global_entry_pair.c */
void set_global_entry_pair(s32 value_18e44, s32 value_18e48);

/* set_global_entry_value_s.c */
void capture_global_entry_value(void);

/* set_script_flag_db3.c */
void set_script_flag_db3(void);

/* shared_script_no_op.c */
void shared_script_no_op(void);

#endif
