#ifndef FRONTEND_LIBCARD_H
#define FRONTEND_LIBCARD_H

struct ObjectNodeHeader;
/* Prototypes of the functions defined in src/frontend/libcard/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_8002290C_arg0.h"
/* Slot-menu payload: the request returns to its owning card chooser. */
typedef struct CardSlotMenuState {
    u8 pad_00[0x20];
    void *request;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x10];
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
} CardSlotMenuState;

struct Node8002BB08;
struct Object13B18;
struct Object_800128C8;
struct S_80022524_0;
struct S_80023258_0;
struct S_80023F94_0;
struct S_80025030_0;
struct S_80026C94_0;
struct S_80027A68_0;
struct S_800491F4;
struct UnkStruct1E;

/* advance_card_boot_stream_pair.c */
void advance_card_boot_stream_pair(s32 record_addr);

/* advance_timed_visual.c */
void advance_timed_visual(s32 *dest, s32 value);

/* assign_object_descriptor_check.c */
void assign_object_descriptor_on_check(void *object_data_addr);

/* build_and_queue_interpolated_vertical_quads_around_five_perimeter_points.c */
void build_and_queue_interpolated_vertical_quads_around_five_perimeter_points(u8 *window_state);

/* build_install.c */
void build_install(u8 *object);

/* card_boot_animate_three_row_selection.c */
s32 card_boot_animate_three_row_selection(struct S_80023258_0 *state);

/* card_boot_apply_slot_deletion_response.c */
void card_boot_apply_slot_deletion_response(void *object);

/* card_boot_begin_selected_value_transition.c */
void card_boot_begin_selected_value_transition(s32 object_addr, s32 value);

/* card_boot_bind_command_panel_resources.c */
void card_boot_bind_command_panel_resources(void *object);

/* card_boot_bind_save_heading_display_data.c */
void card_boot_bind_save_heading_display_data(void *record);

/* card_boot_build_eight_entry_presence_mask.c */
s32 card_boot_build_eight_entry_presence_mask(void);

/* card_boot_build_save_description.c */
void card_boot_build_save_description(s32 record, s32 index);

/* card_boot_build_shaded_panel_packets.c */
void *card_boot_build_shaded_panel_packets(u8 *packet, u32 x, u32 y);

/* card_boot_clear_ten_display_slots.c */
void card_boot_clear_ten_display_slots(void *object);

/* card_boot_close_events_and_resume_timer.c */
void card_boot_close_events_and_resume_timer(void);

/* card_boot_confirm_selected_slot_deletion.c */
void card_boot_confirm_selected_slot_deletion(void *state);

/* card_boot_create_menu_child_panels.c */
void card_boot_create_menu_child_panels(void *record);

/* card_boot_create_save_slot_menu.c */
void *card_boot_create_save_slot_menu(void *init_value, s32 state_value);

/* card_boot_create_slot_selection_menu.c */
void *card_boot_create_slot_selection_menu(void *init_value, s32 unused);

/* card_boot_create_three_row_command_panel.c */
void *card_boot_create_three_row_command_panel(void *init_value);

/* card_boot_destroy_slot_selection_menu.c */
void card_boot_destroy_slot_selection_menu(struct UnkStruct1E *object);

/* card_boot_dispatch_selected_menu_action.c */
void card_boot_dispatch_selected_menu_action(struct Object_800128C8 *object);

/* card_boot_enter_copying_progress.c */
void card_boot_enter_copying_progress(void *object_data);

/* card_boot_enter_insufficient_space_advice.c */
void card_boot_enter_insufficient_space_advice(void *record_part);

/* card_boot_enter_overwrite_confirmation.c */
void card_boot_enter_overwrite_confirmation(void *record_part);

/* card_boot_enter_slot_selection_input.c */
void card_boot_enter_slot_selection_input(void *record_data);

/* card_boot_format_card_with_retry.c */
void card_boot_format_card_with_retry(void *state);

/* card_boot_format_command_panel_labels.c */
void card_boot_format_command_panel_labels(s32 baseAddress);

/* card_boot_format_saved_slot_details.c */
void card_boot_format_saved_slot_details(void *record);

/* card_boot_handle_format_answer.c */
void card_boot_handle_format_answer(void *object);

/* card_boot_handle_message_dialog_input.c */
void card_boot_handle_message_dialog_input(struct S_80022524_0 *menu);

/* card_boot_handle_overwrite_answer.c */
void card_boot_handle_overwrite_answer(void *object_data);

/* card_boot_initialize_paired_choice_layout.c */
void card_boot_initialize_paired_choice_layout(void *record_addr);

/* card_boot_initialize_paired_choice_panel.c */
void card_boot_initialize_paired_choice_panel(s8 *record, s32 initial_value);

/* card_boot_initialize_save_heading_layout.c */
void card_boot_initialize_save_heading_layout(void *object);

/* card_boot_initialize_three_row_command_panel.c */
void card_boot_initialize_three_row_command_panel(void *record, void *init_value);

/* card_boot_layout_five_entry_list.c */
void card_boot_layout_five_entry_list(void *context);

/* card_boot_layout_left_right_labels.c */
void card_boot_layout_left_right_labels(struct S_80026C94_0 *owner);

/* card_boot_layout_three_row_command_panel.c */
void card_boot_layout_three_row_command_panel(void *panel);

/* card_boot_link_paired_choice_display_entries.c */
void card_boot_link_paired_choice_display_entries(struct S_800491F4 **nodes);

/* card_boot_link_three_row_panel_entries.c */
void card_boot_link_three_row_panel_entries(struct S_800491F4 **input);

/* card_boot_mark_object_complete.c */
void card_boot_mark_object_complete(struct ObjectNodeHeader *object);

/* card_boot_open_save_slot_selection.c */
void *card_boot_open_save_slot_selection(void *request);

/* card_boot_open_selected_request_menu.c */
void card_boot_open_selected_request_menu(void *record);

/* card_boot_refresh_five_slot_selection.c */
void card_boot_refresh_five_slot_selection(struct S_80025030_0 *state);

/* card_boot_refresh_paired_choice_labels.c */
void card_boot_refresh_paired_choice_labels(u8 *state);

/* card_boot_render_panel_hierarchy.c */
s16 card_boot_render_panel_hierarchy(s32 first_value, s32 second_value, s32 third_value);

/* card_boot_reset_three_row_highlight.c */
void card_boot_reset_three_row_highlight(void *object);

/* card_boot_restore_saved_selection_callback.c */
void card_boot_restore_saved_selection_callback(void *object_data);

/* card_boot_resume_menu_after_slot_refresh.c */
void card_boot_resume_menu_after_slot_refresh(void *object_data);

/* card_boot_return_from_save_menu.c */
void card_boot_return_from_save_menu(void *record_part);

/* card_boot_return_from_slot_menu.c */
void card_boot_return_from_slot_menu(void *object_data);

/* card_boot_save_selected_slot.c */
void *card_boot_save_selected_slot(void *context);

/* card_boot_select_copy_source_slot.c */
void card_boot_select_copy_source_slot(void *state);

/* card_boot_set_centered_rectangle.c */
s32 card_boot_set_centered_rectangle(s32 target, s32 width, s32 height);

/* card_boot_set_menu_and_panel_selection.c */
void card_boot_set_menu_and_panel_selection(s32 object_addr, s32 state_value);

/* card_boot_set_paired_choice_animations.c */
void card_boot_set_paired_choice_animations(struct Object13B18 *object, s32 *enable_flags, s32 *active_flags);

/* card_boot_set_slot_details_selection.c */
void card_boot_set_slot_details_selection(s32 object_addr, s32 value_7c, s32 value_80);

/* card_boot_set_slot_index_and_owner.c */
void card_boot_set_slot_index_and_owner(struct S_80023F94_0 *pair, s32 second, s32 first);

/* card_boot_set_slot_selection_marker.c */
void card_boot_set_slot_selection_marker(s32 object_addr, s32 enable_table);

/* card_boot_show_copy_failure_notice.c */
void card_boot_show_copy_failure_notice(s32 value);

/* card_boot_show_copying_progress.c */
void card_boot_show_copying_progress(s32 owner, s32 data);

/* card_boot_show_damaged_memory_card_notice.c */
void card_boot_show_damaged_memory_card_notice(s32 value);

/* card_boot_show_delete_confirmation.c */
void card_boot_show_delete_confirmation(s32 owner, s32 data);

/* card_boot_show_delete_failure_notice.c */
void card_boot_show_delete_failure_notice(s32 command_arg);

/* card_boot_show_format_confirmation.c */
void card_boot_show_format_confirmation(s32 request_id, s32 request_value);

/* card_boot_show_format_failure_notice.c */
void card_boot_show_format_failure_notice(s32 value);

/* card_boot_show_format_success_notice.c */
void card_boot_show_format_success_notice(s32 input_value);

/* card_boot_show_formatting_progress.c */
void card_boot_show_formatting_progress(s32 owner, s32 status_flag);

/* card_boot_show_insufficient_space_card_advice.c */
void card_boot_show_insufficient_space_card_advice(s32 value);

/* card_boot_show_insufficient_space_overwrite_advice.c */
void card_boot_show_insufficient_space_overwrite_advice(s32 value);

/* card_boot_show_loading_progress.c */
void card_boot_show_loading_progress(s32 parent, s32 status);

/* card_boot_show_no_memory_card_notice.c */
void card_boot_show_no_memory_card_notice(s32 context);

/* card_boot_show_no_saved_game_notice.c */
void card_boot_show_no_saved_game_notice(s32 value);

/* card_boot_show_overwrite_confirmation.c */
void card_boot_show_overwrite_confirmation(s32 owner, s32 data);

/* card_boot_show_overwrite_failure_notice.c */
void card_boot_show_overwrite_failure_notice(s32 owner);

/* card_boot_show_overwrite_protected_notice.c */
void card_boot_show_overwrite_protected_notice(s32 value);

/* card_boot_show_please_wait_notice.c */
void card_boot_show_please_wait_notice(s32 input, s32 value);

/* card_boot_show_saving_progress.c */
void card_boot_show_saving_progress(s32 target, s32 value);

/* card_boot_start_hardware_counter.c */
void card_boot_start_hardware_counter(void);

/* card_boot_stop_timer_and_init_server.c */
void card_boot_stop_timer_and_init_server(void);

/* card_boot_sum_slot_lookup_values.c */
s32 card_boot_sum_slot_lookup_values(void);

/* card_boot_update_card_chooser_input.c */
void card_boot_update_card_chooser_input(void *menu);

/* card_boot_update_copy_destination_selection.c */
void card_boot_update_copy_destination_selection(u8 *menu);

/* card_boot_wait_before_copying_slot.c */
void card_boot_wait_before_copying_slot(void *record_data);

/* card_boot_wait_before_formatting_card.c */
void card_boot_wait_before_formatting_card(void *record_data);

/* card_boot_wait_before_loading_slot.c */
void card_boot_wait_before_loading_slot(void *record_data);

/* card_boot_wait_before_saving_slot.c */
void card_boot_wait_before_saving_slot(void *record_data);

/* create_save_heading.c */
void *create_save_heading(s32 init_value);

/* create_visual_object.c */
void *create_visual_object(s32 init_value, s32 stored_value);

/* dialog_packet_setup_g00380.c */
void *card_boot_build_paired_dialog_packets(void *buffer, s32 unused);
void card_boot_initialize_dialog_packets_and_display(s32 record);

/* dialog_selection_highlight_g00379.c */
void card_boot_highlight_dialog_text_range(s32 entry_base, s32 start_index, s32 entry_count);
void card_boot_position_dialog_selection_marker(void *context, s32 column, s32 mode, s32 row, s32 row_value);
void card_boot_update_message_choice_highlight(void *object);

/* dispatch_menu_update_callback.c */
void *dispatch_menu_update_callback(void *request);

/* dispatch_request_mode_two.c */
void *dispatch_request_mode_two(void *request);

/* draw_cylindrical.c */
void draw_cylindrical(void *object);

/* entry_card_boot_has_selected_channel.c */
void card_boot_init_channel_record(struct S_80027A68_0 *record, void *request, s32 value_00);

/* init_card_boot_request_object.c */
struct Node8002BB08 *init_card_boot_request_object(void *request, s32 mode);

/* libcard_init.c */
void libcard_init(s32 slot);

/* libcard_query_status.c */
s16 libcard_query_status(void);

/* libcard_select_slot.c */
void libcard_select_slot(s32 slot);

/* libcard_start.c */
void libcard_start(void);

/* libcard_stop.c */
void libcard_stop(void);

/* link_save_heading_draw_nodes.c */
struct S_800491F4 *link_save_heading_draw_nodes(void *input);

/* message_dialog_lifecycle_g00381.c */
void card_boot_measure_five_line_message(u8 *text_block);
void card_boot_bind_message_dialog_record(Rec_func_8002290C_arg0 *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
void card_boot_initialize_message_dialog_layout(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
void card_boot_activate_message_dialog(void *object);
u8 *card_boot_create_or_reset_message_dialog(s32 value_14, void *entry_index, void *value_0c, s32 value_20);

/* occupied_slot_window_g00386.c */
void card_boot_format_occupied_slot_window(void *slot_owner);
void card_boot_layout_alternate_slot_window(void *context);
void card_boot_populate_slot_window_display(s32 *state);

/* process_nonzero.c */
void process_nonzero(void *record);

/* render_rotated_grid_surface.c */
void *render_rotated_grid_surface(s32 parent, s32 context, s32 mode);

/* route_save_slot_validation.c */
void route_save_slot_validation(void *context);

/* set_entry_destination_and_value.c */
void set_entry_destination_and_value(void *state);

/* set_record_pair_to_one.c */
void set_record_pair_to_one(CardSlotMenuState *record);

/* slot_detail_refresh_g00388.c */
void card_boot_format_empty_slot_guidance(void *context);
void build_a_trigonometric_table_processes_up_eight_height_offset_segments(void *context);

/* update_effect_color_rotation_and_motion.c */
void func_80024C48(struct S_800491F4 **target);
void update_effect_color_rotation_and_motion(struct S_800491F4 **target);

/* update_inventory_menu.c */
void update_inventory_menu(void *state_arg);

/* update_record_and_install_next_table.c */
void update_record_and_install_next_table(void *record_data);

/* update_spark_effect.c */
void update_spark_effect(void *menu);

/* write_fixed_palette_pixels.c */
void write_fixed_palette_pixels(void *owner);

struct CardFileListPanel;
void init_card_file_list_panel(struct CardFileListPanel *panel, s32 selection);

typedef struct CardHeadingTemplate {
    s32 word0, word1, word2, word3;
} CardHeadingTemplate;

typedef struct CardHeadingCommon {
    s32 word0, word1, word2;
} CardHeadingCommon;

typedef struct CardHeadingDrawNode {
    s32 unused;
    CardHeadingTemplate *command;
    CardHeadingCommon *common;
    s32 reserved;
} CardHeadingDrawNode;

typedef struct CardHeadingDrawState {
    u8 pad_00[0xD4];
    CardHeadingCommon common;
    u8 pad_E0[0x0C];
    struct S_800491F4 *chain;
    CardHeadingDrawNode *links[4];
    CardHeadingDrawNode nodes[4];
    CardHeadingTemplate commands[4];
} CardHeadingDrawState;

extern CardHeadingTemplate D_8002E5D8;
extern CardHeadingCommon D_8002E5E8;

void initialize_save_heading_draw_state(CardHeadingDrawState *work, s32 count);

#endif
