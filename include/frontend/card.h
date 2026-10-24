#ifndef FRONTEND_CARD_H
#define FRONTEND_CARD_H
/* Prototypes of the functions defined in src/frontend/card/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct MainPacket12;
struct MainValue;
struct Menu;
struct Object_8001F2F4;
struct Owner8001D8F8;
struct S_8001B93C_0;
struct S_8001B974_0;
struct S_8001B974_1;
struct S_8001B974_2;
struct S_8001BEA4_0;
struct S_8001CD7C_0;
struct S_8001CDA0_0;
struct S_8001CDA0_1;
struct S_8001CDA0_2;
struct S_8001D668_0;
struct S_8001EC4C_0;
struct S_8001F568_0;
struct S_8001FF0C_0;
struct S_80020458_2;
struct S_80020D0C_0;
struct S_80021394_0;
struct S_80026720_0;

/* bind_dialog_template.c */
void bind_dialog_template(s32 target);

/* build_memory_task_text.c */
void build_memory_task_text(s32 panel_addr);

/* card_animate_selection_marker_rows.c */
void card_animate_selection_marker_rows(struct Menu *menu);

/* card_background_bind_dialog_template.c */
void card_background_bind_dialog_template(s32 context);

/* card_background_bind_template.c */
void card_background_bind_template(s32 context);

/* card_background_build_border_packets.c */
void *card_background_build_border_packets(void *buffer, s32 width, s32 height);

/* card_background_build_draw_packets.c */
struct MainPacket12 *card_background_build_draw_packets(struct MainPacket12 *packet);

/* card_background_init_components.c */
void card_background_init_components(s32 object_addr);

/* card_background_init_entry_tables.c */
void card_background_init_entry_tables(void *object, s32 entry_count);

/* card_background_init_overlay_prims.c */
void *card_background_init_overlay_prims(u8 *record);

/* card_background_init_prims.c */
void *card_background_init_prims(u8 *record);

/* card_background_layout_entries.c */
void card_background_layout_entries(struct Owner8001D8F8 *owner);

/* card_background_set_word.c */
void card_background_set_word(s32 *dest, s32 value);

/* card_boot_jump_to_menu_code_entry.c */
void card_boot_jump_to_menu_code_entry(void);

/* card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected.c */
void card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected(void *state, s32 *enabled, s32 *selected);

/* card_build_selected_slot_details.c */
void card_build_selected_slot_details(void *panel);

/* card_choice_state.c */
void card_boot_set_paired_choice_selection(s32 object_addr, s32 value);
void card_boot_update_paired_choice_animations(s32 base_addr, s32 *enable_flags, s32 *active_flags);

/* card_dev_advance_boot_step.c */
s32 card_dev_advance_boot_step(void);

/* card_dev_begin_value_transition.c */
void card_dev_begin_value_transition(struct S_8001CD7C_0 *object, s32 new_value);

/* card_dev_bind_info_template.c */
void card_dev_bind_info_template(s32 context);

/* card_dev_bind_panel_template.c */
void card_dev_bind_panel_template(s32 context);

/* card_dev_bind_row_labels.c */
void card_dev_bind_row_labels(s32 baseAddress);

/* card_dev_bind_slot_label.c */
void card_dev_bind_slot_label(s32 object_addr);

/* card_dev_bind_slot_rows_template.c */
void card_dev_bind_slot_rows_template(s32 context);

/* card_dev_build_slot_path.c */
void card_dev_build_slot_path(s32 target, s32 entry_index);

/* card_dev_cache_slot_summary.c */
void card_dev_cache_slot_summary(void);

/* card_dev_calc_remaining_8k_blocks.c */
s32 card_dev_calc_remaining_8k_blocks(s32 entry_count);

/* card_dev_clear_object_state.c */
void card_dev_clear_object_state(void *record_data);

/* card_dev_clear_op_busy.c */
s32 card_dev_clear_op_busy(void);

/* card_dev_clear_op_failed.c */
s32 card_dev_clear_op_failed(void);

/* card_dev_clear_ten_values.c */
void card_dev_clear_ten_values(void *state);

/* card_dev_close_events.c */
void card_dev_close_events(void);

/* card_dev_commit_pending_value.c */
void card_dev_commit_pending_value(void *record_data);

/* card_dev_count_cached_slots.c */
s32 card_dev_count_cached_slots(void);

/* card_dev_create_slot_screen_objects.c */
void card_dev_create_slot_screen_objects(u8 *work);

/* card_dev_dispatch_callback_by_index.c */
void card_dev_dispatch_callback_by_index(struct Object_8001F2F4 *object);

/* card_dev_drain_hw_events.c */
void card_dev_drain_hw_events(void);

/* card_dev_drain_sw_events.c */
void card_dev_drain_sw_events(void);

/* card_dev_enter_mode_default_effect.c */
void card_dev_enter_mode_default_effect(void *owner);

/* card_dev_enter_mode_first_effect.c */
void card_dev_enter_mode_first_effect(void *owner);

/* card_dev_enter_mode_second_effect.c */
void card_dev_enter_mode_second_effect(void *owner);

/* card_dev_event_error_handler.c */
s32 card_dev_event_error_handler(void);

/* card_dev_event_ioe_handler.c */
s32 card_dev_event_ioe_handler(void);

/* card_dev_event_new_handler.c */
s32 card_dev_event_new_handler(void);

/* card_dev_event_timeout_handler.c */
s32 card_dev_event_timeout_handler(void);

/* card_dev_flag_object_dirty.c */
void card_dev_flag_object_dirty(void *object);

/* card_dev_flag_slot_dirty.c */
void card_dev_flag_slot_dirty(s32 card_slot);

/* card_dev_get_op_state.c */
s32 card_dev_get_op_state(void);

/* card_dev_get_remaining_block_summary.c */
s32 card_dev_get_remaining_block_summary(void);

/* card_dev_get_slot_marker.c */
s32 card_dev_get_slot_marker(s32 record_index);

/* card_dev_has_selected_channel.c */
s32 card_dev_has_selected_channel(void);

/* card_dev_init.c */
void card_dev_init(void);

/* card_dev_init_output_pointers.c */
void card_dev_init_output_pointers(void *record);

/* card_dev_init_row_layout.c */
void card_dev_init_row_layout(void *record_groups);

/* card_dev_init_row_panel.c */
void card_dev_init_row_panel(void *panel);

/* card_dev_init_row_tables.c */
void card_dev_init_row_tables(void *object);

/* card_dev_init_row_view.c */
void card_dev_init_row_view(struct S_8001CDA0_2 *entry, struct S_8001CDA0_0 *placement, struct S_8001CDA0_1 *settings, s32 row_index);

/* card_dev_init_slot_rows.c */
void card_dev_init_slot_rows(s32 slot_addr);

/* card_dev_init_two_rows.c */
void card_dev_init_two_rows(s32 record_addr);

/* card_dev_init_view_defaults.c */
void card_dev_init_view_defaults(struct S_8001B974_2 *state, struct S_8001B974_0 *main_config, struct S_8001B974_1 *aux_config);

/* card_dev_layout_option_entries.c */
void card_dev_layout_option_entries(u8 *object);

/* card_dev_layout_selected_slot_entries.c */
void card_dev_layout_selected_slot_entries(u8 *screen);

/* card_dev_layout_title_entries.c */
void card_dev_layout_title_entries(u8 *owner);

/* card_dev_layout_two_rows.c */
void card_dev_layout_two_rows(void *object);

/* card_dev_layout_two_rows_callbacks.c */
void card_dev_layout_two_rows_callbacks(struct S_80020458_2 *owner);

/* card_dev_load_forward_object_value.c */
void card_dev_load_forward_object_value(void *object, s32 value);

/* card_dev_load_set_object_value.c */
void card_dev_load_set_object_value(struct S_8001FF0C_0 *object, s32 value);

/* card_dev_load_slot_metadata.c */
s32 card_dev_load_slot_metadata(s32 slot_index);

/* card_dev_load_wait_countdown.c */
void card_dev_load_wait_countdown(void *record_data);

/* card_dev_menu_wait_countdown.c */
void card_dev_menu_wait_countdown(void *record_data);

/* card_dev_no_op_save.c */
void card_dev_no_op_save(void);

/* card_dev_open_events.c */
void card_dev_open_events(s32 unused0, s32 unused1, s32 unused2, s32 unused3);

/* card_dev_print_status.c */
void card_dev_print_status(void);

/* card_dev_read_file_units_128.c */
s32 card_dev_read_file_units_128(s32 file_path, void *buffer, s32 block_count, s32 block_offset);

/* card_dev_refresh_options_object.c */
void card_dev_refresh_options_object(void *object);

/* card_dev_refresh_save_screen.c */
void release_card_screen_parts(void *object);

/* card_dev_refresh_slot_outputs.c */
void card_dev_refresh_slot_outputs(s32 value, s32 *enabled, s32 *selected);

/* card_dev_reset_object_tint.c */
void card_dev_reset_object_tint(struct S_8001D668_0 *object);

/* card_dev_run_init_hook.c */
void card_dev_run_init_hook(void);

/* card_dev_run_temp_slot_operation.c */
void card_dev_run_temp_slot_operation(void);

/* card_dev_save_wait_countdown.c */
void card_dev_save_wait_countdown(void *record_data);

/* card_dev_select_slot_callback.c */
void card_dev_select_slot_callback(u8 *task);

/* card_dev_select_sub_block.c */
void card_dev_select_sub_block(void *obj);

/* card_dev_set_object_value.c */
void card_dev_set_object_value(struct S_8001F568_0 *object, s32 value);

/* card_dev_set_record_fields.c */
void card_dev_set_record_fields(struct S_80021394_0 *record, s32 value_14, s32 value_00);

/* card_dev_set_slot_value_checked.c */
void card_dev_set_slot_value_checked(s32 slot_addr, s32 slot_value);

/* card_dev_set_word.c */
void card_dev_set_word(s32 *dest, s32 value);

/* card_dev_show_copy_failure_notice.c */
void card_dev_show_copy_failure_notice(s32 value);

/* card_dev_show_copying_progress.c */
void card_dev_show_copying_progress(s32 target, s32 value);

/* card_dev_show_damaged_memory_card_notice.c */
void card_dev_show_damaged_memory_card_notice(s32 value);

/* card_dev_show_delete_confirmation.c */
void card_dev_show_delete_confirmation(s32 context, s32 value);

/* card_dev_show_delete_failure_notice.c */
void card_dev_show_delete_failure_notice(s32 target);

/* card_dev_show_format_confirmation.c */
void card_dev_show_format_confirmation(s32 target, s32 value);

/* card_dev_show_format_failure_notice.c */
void card_dev_show_format_failure_notice(s32 input);

/* card_dev_show_format_success_notice.c */
void card_dev_show_format_success_notice(s32 target);

/* card_dev_show_formatting_progress.c */
void card_dev_show_formatting_progress(s32 target, s32 value);

/* card_dev_show_insufficient_space_card_advice.c */
void card_dev_show_insufficient_space_card_advice(s32 value);

/* card_dev_show_insufficient_space_overwrite_advice.c */
void card_dev_show_insufficient_space_overwrite_advice(s32 target);

/* card_dev_show_load_failure_notice.c */
void card_dev_show_load_failure_notice(s32 target);

/* card_dev_show_loading_progress.c */
void card_dev_show_loading_progress(s32 context, s32 payload);

/* card_dev_show_no_memory_card_notice.c */
void card_dev_show_no_memory_card_notice(s32 value);

/* card_dev_show_overwrite_confirmation.c */
void card_dev_show_overwrite_confirmation(s32 target, s32 value);

/* card_dev_show_overwrite_failure_notice.c */
void card_dev_show_overwrite_failure_notice(s32 value);

/* card_dev_show_overwrite_protected_notice.c */
void card_dev_show_overwrite_protected_notice(s32 target);

/* card_dev_show_please_wait_notice.c */
void card_dev_show_please_wait_notice(s32 target, s32 value);

/* card_dev_show_saving_progress.c */
void card_dev_show_saving_progress(s32 target, s32 value);

/* card_dev_start_default_screen.c */
void card_dev_start_default_screen(void);

/* card_dev_start_next_screen.c */
void card_dev_start_next_screen(struct S_8001EC4C_0 *object);

/* card_dev_store_save_xor_checksum.c */
void card_dev_store_save_xor_checksum(void *gsw);

/* card_dev_store_word.c */
void card_dev_store_word(void **dest, void *value);

/* card_dev_update_load_slot_highlight.c */
void card_dev_update_load_slot_highlight(void *record_data);

/* card_dev_update_menu_input.c */
void card_dev_update_menu_input(u8 *root);

/* card_dev_update_save_slot_selection.c */
void card_dev_update_save_slot_selection(void *record_data);

/* card_dev_update_slot_pair_rows.c */
void card_dev_update_slot_pair_rows(u8 *object);

/* card_dev_verify_save_xor_checksum.c */
s32 card_dev_verify_save_xor_checksum(void *gsw);

/* card_dev_wait_poll_ready.c */
s32 card_dev_wait_poll_ready(s32 poll_id);

/* card_dev_write_file_units_128.c */
s32 card_dev_write_file_units_128(s32 filename, void *buffer, s32 block_count, s32 block_offset, s32 skip_create);

/* card_dev_write_save_via_temporary_path.c */
s32 card_dev_write_save_via_temporary_path(s32 entry_id, s32 request_id);

/* card_devkit_set_window_selection_marker.c */
void card_devkit_set_window_selection_marker(void *basePtr, s32 flag);

/* card_directory_operations_g00377.c */
s32 count_entries_matching_search_path(void);
s32 card_boot_calc_remaining_8k_blocks(s32 entry_count);
s32 card_boot_has_directory_name_prefix(s32 count, u8 *text);
s32 card_boot_format_card_and_wait(s32 card_slot);
void card_boot_build_slot_path(s32 dest, s32 suffix_index);

/* card_info_bind_template.c */
void card_info_bind_template(s32 value);

/* card_info_set_value_and_refresh.c */
void card_info_set_value_and_refresh(void *object, s32 value);

/* card_info_set_word.c */
void card_info_set_word(s32 *dest, s32 value);

/* card_save_request.c */
void card_boot_set_save_menu_request(struct S_80026720_0 *object, void *value);
void card_boot_initialize_save_menu_request(void *object, void *value);

/* card_slot_menu_request.c */
void card_boot_initialize_slot_menu_request(void *object, void *value);

/* card_slot_records.c */
void inventory_copy_and_sign_extend_record_fields(s32 object_data);
void card_boot_refresh_five_slot_objects(void *object_list);

/* card_slot_refresh.c */
void card_boot_clear_slot_selection_marker(s32 object_addr);
void card_boot_refresh_slot_window(s32 object_addr);

/* card_sme_commit_pending_value.c */
void card_sme_commit_pending_value(void *record_data);

/* card_sme_fade_entry.c */
void card_sme_fade_entry(struct S_80020D0C_0 *object);

/* card_sme_set_word.c */
void card_sme_set_word(s32 *dest, s32 value);

/* center_view_on_object.c */
void center_view_on_object(void *object);

/* clear_card_selection_flag.c */
void clear_card_selection_flag(void);

/* clear_global_if_value_zero.c */
void clear_global_if_value_zero(struct S_8001B93C_0 *object);

/* complete_pending_object_state.c */
void complete_pending_object_state(s32 *ptr);

/* fade_four_entries.c */
void fade_four_entries(void *object);

/* fill_value_output_fields.c */
void fill_value_output_fields(struct MainValue **value_slot, u8 *output, struct MainValue *value);

/* find_text_word_bounds.c */
void find_text_word_bounds(u8 *text, s32 limit, s32 *start_out, s32 *length_out, s32 *total_out);

/* handle_object_menu_input.c */
void select_card_slot_message(void *task);

/* init_card_background_object.c */
s32 init_card_background_object(s32 init_value, s32 config_value);

/* init_card_info_object.c */
void *init_card_info_object(s32 init_option, s32 info_value);

/* init_card_options_object.c */
s32 init_card_options_object(s32 option_param);

/* init_card_slot_object.c */
void *init_card_slot_object(s32 init_option);

/* init_card_sme_object.c */
s32 init_card_sme_object(s32 init_option);

/* init_card_window_slot_object.c */
void init_card_window_slot_object(s32 init_value, s32 slot_index);

/* init_dialog_object.c */
void init_dialog_object(s32 object_addr);

/* init_frame_primitive_pairs.c */
void *init_frame_primitive_pairs(void *buffer);

/* init_menu_entry_pointers.c */
void init_menu_entry_pointers(void *state, s32 entry_count);

/* init_menu_row_entry.c */
void *init_menu_row_entry(void *context, void *entry, s32 row_index);

/* mark_object_flags_dirty.c */
void func_80089A14(unsigned short *data);
void mark_object_flags_dirty(unsigned short *data);

/* no_op_card_hook.c */
void no_op_card_hook(void);

/* refresh_object_value.c */
void refresh_object_value(void *object);

/* reset_card_selection_state.c */
void reset_card_selection_state(void);

/* run_flag_handler_set_flags.c */
void run_flag_handler_and_set_2000_flags(void *entry);

/* save_copy_completion_g00392.c */
void initialize_save_description(void *owner, s32 value);
void process_five_context_entries_or_fallback(void *context);

/* save_file_updates_g00378.c */
s32 card_boot_verify_save_xor_checksum(void *save_data);
s32 card_boot_write_save_via_temporary_path(s32 slot, void *data);
void card_boot_load_save_and_clear_marker(s32 entry_index, void *data, s32 update_entry);

/* set_layout_params.c */
void set_layout_params(struct S_8001BEA4_0 *record, s32 value_14, s32 value_08, s32 value_0c, s32 value_20);

/* toggle_card_selection_state.c */
void toggle_card_selection_state(void);

/* update_global_dialog_state.c */
s32 update_global_dialog_state(s32 flag_linked_object);

/* update_object_and_flag_linked.c */
void update_object_and_flag_linked(void *object_data, s32 first_value, s32 second_value);

void card_boot_open_events(void);
void card_boot_init_server(void);
void card_boot_close_events(void);

#endif
