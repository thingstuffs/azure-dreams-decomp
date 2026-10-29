#ifndef TOWN_DEVKIT_H
#define TOWN_DEVKIT_H
/* Prototypes of the functions defined in src/town/devkit/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct CopyBlock;
struct OvWork;
struct S_802EE4E8_0;

/* advance_stage_1_when_ready.c */
s32 advance_stage_1_when_ready(s32 entry);

/* call_devkit_callback_at_first_failure.c */
s32 call_devkit_callback_at_first_failure(void);

/* call_helper_fixed_id.c */
s32 call_helper_with_fixed_id_1(void);

/* call_helper_fixed_id_b.c */
s32 call_helper_with_fixed_id_2(void);

/* call_helper_fixed_id_c.c */
s32 call_helper_with_fixed_id_3(void);

/* call_helper_fixed_id_d.c */
s32 call_helper_with_fixed_id_4(void);

/* call_helper_fixed_id_e.c */
s32 call_helper_with_fixed_id_5(void);

/* call_helper_fixed_id_f.c */
s32 call_helper_with_fixed_id_6(void);

/* check_devkit_secondary_condition.c */
s32 check_devkit_secondary_condition(s32 value_index);

/* clear_stored_id_bits.c */
void clear_stored_id_bits(void);

/* copy_devkit_scene_step_reset.c */
s32 copy_devkit_scene_step_reset(void);

/* copy_overlay_work_record_trace.c */
void copy_overlay_work_record_trace(struct OvWork *p);

/* copy_scene_buffer_data.c */
void copy_scene_buffer_data(struct CopyBlock *source);

/* copy_shop_runtime_callback_devkit.c */
void copy_shop_runtime_callback_devkit(void);

/* copy_trace_overlay_work_record.c */
void copy_and_trace_overlay_work_record(struct OvWork *p);

/* dev_copy_overlay_work_and_trace.c */
void dev_copy_overlay_work_and_trace_47(s32 *p);

/* dev_copy_overlay_work_and_trace_48.c */
void dev_copy_overlay_work_and_trace_48(s8 *overlay_state);

/* dev_dispatch_flag_test_and_get_result_alt.c */
s32 dev_dispatch_flag_test_and_get_result_alt(void);

/* dev_report_kind_mode_sno.c */
void dev_report_kind_mode_sno(s32 kind);

/* dev_report_kind_mode_sno_alt.c */
void dev_report_kind_mode_sno_alt(s32 kind);

/* dispatch_by_leading_id_flags.c */
s32 dispatch_by_leading_id_flags(void);

/* dispatch_devkit_callback_by_run_length.c */
void dispatch_devkit_callback_by_run_length(void);

/* dispatch_first_rejected_entry.c */
s32 dispatch_first_rejected_entry(void);

/* entry_pass_indexed_table.c */
s32 set_stage_flag_one_if_ready(s32 fallback_result);

/* find_callback_value_index.c */
s32 find_callback_value_index(void);

/* find_devkit_callback_value_index.c */
s32 find_devkit_callback_value_index(void);

/* finish_stage_for_index.c */
s32 finish_stage_for_index(s32 index);

/* grid_process_six_entry_pairs_a.c */
void grid_process_six_entry_pairs_a(void);

/* grid_process_six_entry_pairs_b.c */
void grid_process_six_entry_pairs_b(void);

/* grid_resolve_indexed_records.c */
void grid_resolve_indexed_records(s32 list_index);

/* grid_run_bit_set_operation_a.c */
void grid_run_bit_set_operation_a(s32 row, s32 column);

/* grid_run_bit_set_operation_b.c */
void grid_run_bit_set_operation_b(s32 row, s32 column);

/* grid_run_indexed_operation_a.c */
s32 grid_run_indexed_operation_a(s32 table_index, s32 call_input, s32 call_param, s32 call_extra);

/* grid_run_indexed_operation_b.c */
s32 grid_run_indexed_operation_b(s32 table_index, s32 call_input, s32 call_param);

/* handle_devkit_page_value.c */
s32 handle_devkit_page_2_value(s32 carry_value);

/* invoke_indexed_runtime_operation.c */
void invoke_indexed_runtime_operation(s32 scene_index);

/* load_scene_data_block.c */
void load_scene_data_block(s32 scene, s32 mode);

/* memory_init_work_object_and_callback.c */
void *memory_init_work_object_and_callback(s32 init_value_a, s32 init_value_b);

/* noop_hook_k.c */
void noop_hook_k(void);

/* pass_indexed_devkit_value.c */
void pass_indexed_devkit_value(s32 index);

/* pass_indexed_table.c */
s32 set_stage_flag_two_if_ready(s32 fallback_result);

/* process_memory_target_fixed_parameters.c */
void process_memory_target_fixed_parameters(s32 target);

/* process_memory_target_mode_one.c */
void process_memory_target_mode_one(s32 target);

/* process_memory_target_mode_zero.c */
void process_memory_target_mode_zero(s32 target);

/* process_table_entry_pair.c */
void process_table_entry_pair(void);

/* read_selected_table_value.c */
s32 read_selected_table_value(void);

/* redraw_busy_entry_list.c */
void redraw_busy_entry_list(void);

/* redraw_devkit_list_and_rekey_rows.c */
void redraw_devkit_list_and_rekey_rows(void);

/* refresh_status_when_alt_gate_passes.c */
s32 refresh_status_when_alt_gate_passes(s32 entry);

/* refresh_status_when_gate_and_counter_pass.c */
s32 dispatch_scene_stage_if_counter_positive(s32 fallback_result);

/* refresh_status_when_second_gate_passes.c */
s32 refresh_status_when_second_gate_passes(s32 entry);

/* register_object_handles_and_flag.c */
void register_object_handles_and_flag(void *object);

/* reset_cursor_and_redraw_list.c */
s32 reset_cursor_and_redraw_list(void);

/* rounded_bit_index.c */
void clear_six_devkit_bitmap_bits(void);

/* run_devkit_page_redraw_scan.c */
s32 run_devkit_page_0_redraw_scan(void);

/* run_memory_callbacks.c */
void run_memory_callbacks(void);

/* run_memory_setup_sequence.c */
void run_memory_setup_sequence(void *context);

/* run_memory_setup_with_zero.c */
void run_memory_setup_with_zero(void);

/* run_stage_updates_when_ready.c */
s32 run_stage_updates_when_ready(s32 entry);

/* scale_stored_value_and_base.c */
void scale_stored_value_and_base(void);

/* scale_stored_value_and_base_alt.c */
void scale_stored_value_and_base_alt(void);

/* select_memory_task_exit.c */
void select_memory_task_exit(struct S_802EE4E8_0 *object);

/* set_devkit_value_to_nine.c */
void set_devkit_value_to_nine(void);

/* set_global_object_field_f.c */
int set_global_object_field_12_f_4(void);

/* set_overlay_kind_from_callback.c */
void set_overlay_kind_from_callback(void);

/* set_slot_bit_when_allowed.c */
s32 set_slot_bit_when_allowed(s32 slot, s32 query_b, s32 query_c, s32 query_d);

/* shift_index_and_add_offset_b.c */
void shift_index_and_add_offset_b(void);

/* shift_index_and_add_offset_c.c */
void shift_index_and_add_offset_c(void);

/* shop_advance_entry_step.c */
s32 advance_selected_flag_row(s32 index);

/* shop_dispatch_entry_value.c */
void propagate_indexed_flag_pair(s32 entry_index);

/* shop_find_first_eligible_entry.c */
s32 advance_clear_flag_row(void);

/* shop_get_current_entry_value.c */
s32 shop_get_current_entry_value(void);

/* shop_get_entry_value_or_fallback.c */
s32 read_flag_row_fallback(void);

/* shop_get_global_value.c */
s32 read_stored_runtime_word(void);

/* shop_get_indexed_value_at_f.c */
s32 shop_get_indexed_value_at_1_f_98(void);

/* shop_get_indexed_value_at_fa.c */
s32 shop_get_indexed_value_at_1_fa_8(void);

/* shop_process_entry_pairs.c */
void clear_three_flag_pairs(void);

/* shop_read_selected_row_value.c */
s32 read_flag_row_report(void);

/* shop_run_open_sequence.c */
s32 initialize_flag_selection(void);

/* shop_skip_accepted_entries.c */
s32 test_flag_list_terminator(s32 list_index);

/* store_state_byte_and_return.c */
s32 store_state_byte_and_return(s32 value);

/* trace_work_record_kinds.c */
void trace_work_record_kinds(struct OvWork *p);

/* trigger_selected_entry_operation.c */
void trigger_selected_entry_operation(s32 row, s32 column);

/* update_flag_page_2_value.c */
s32 update_flag_page_2_value(s32 carry_value);

/* update_indexed_flag_and_selection.c */
s32 update_flagged_selection_index(s32 initial_index, s32 input1, s32 input2, s32 input3);

/* update_input_flag_and_selection.c */
s32 update_selection_mask_and_status(s32 index, s32 input_a, s32 input_b, s32 input_c);

#endif
