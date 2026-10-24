#ifndef FRONTEND_LIBCARD_INTERFACES_H
#define FRONTEND_LIBCARD_INTERFACES_H

#include "common.h"

/* MAIN frontend contracts. Context pointers retain their existing opaque views. */
void card_boot_begin_selected_value_transition(s32 object_addr, s32 value);
void card_boot_bind_command_panel_resources(void *object);
void card_boot_bind_save_heading_display_data(void *record);
s32 card_boot_build_eight_entry_presence_mask(void);
void card_boot_close_events_and_resume_timer(void);
void *card_boot_create_save_slot_menu(void *init_value, s32 state_value);
void card_boot_handle_overwrite_answer(void *object_data);
void card_boot_initialize_paired_choice_layout(void *record_addr);
void card_boot_initialize_three_row_command_panel(void *record, void *init_value);
void func_80023730(void *sprite, void *data, void *context);
void card_boot_layout_five_entry_list(void *context);
void card_boot_layout_three_row_command_panel(void *panel);
void card_boot_position_dialog_selection_marker(void *context, s32 column, s32 mode, s32 row, s32 row_value);
void card_boot_refresh_paired_choice_labels(u8 *state);
void card_boot_reset_three_row_highlight(void *object);
void card_boot_resume_menu_after_slot_refresh(void *object_data);
void card_boot_show_copying_progress(s32 owner, s32 data);
void card_boot_show_insufficient_space_overwrite_advice(s32 value);
void card_boot_show_overwrite_confirmation(s32 owner, s32 data);
void card_boot_stop_timer_and_init_server(void);
s32 card_boot_sum_slot_lookup_values(void);
void card_boot_update_card_chooser_input(void *menu);
void card_boot_wait_before_copying_slot(void *record_data);
void route_save_slot_validation(void *context);

#endif
