#ifndef FRONTEND_LIBCARD_MESSAGE_H
#define FRONTEND_LIBCARD_MESSAGE_H
/* Prototypes of the functions defined in src/frontend/libcard/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct Entity;
struct S_800226A8_0;
struct S_8002742C_0;
struct S_800491F4;

/* card_boot_build_message_window_packets.c */
void *card_boot_build_message_window_packets(void *buffer, void *layout);

/* card_boot_center_message_dialog_display.c */
void card_boot_center_message_dialog_display(void *object);

/* card_boot_close_dialog_when_response_clears.c */
void card_boot_close_dialog_when_response_clears(struct S_800226A8_0 *record);

/* card_boot_close_message_dialog.c */
s32 card_boot_close_message_dialog(s32 flagLinkedRecord);

/* card_boot_create_slot_window.c */
void *card_boot_create_slot_window(s32 parent_object, s32 object_index);

/* card_boot_initialize_dialog_draw_nodes.c */
void card_boot_initialize_dialog_draw_nodes(struct Entity *entity, s32 node_count);

/* card_boot_initialize_slot_window.c */
void card_boot_initialize_slot_window(s32 record, s32 setup_value, s32 processing_value);

/* card_boot_layout_empty_slot_window.c */
void card_boot_layout_empty_slot_window(void *object);

/* card_boot_link_message_display_entries.c */
void card_boot_link_message_display_entries(struct S_800491F4 **input);

/* card_boot_link_slot_window_entries.c */
void card_boot_link_slot_window_entries(struct S_800491F4 **value);

/* card_boot_measure_dialog_choice_word.c */
void card_boot_measure_dialog_choice_word(u8 *text, s32 word_index, s32 *offset_out, s32 *length_out, s32 *prior_chars_out);

/* card_boot_prepare_copy_destination_message.c */
void card_boot_prepare_copy_destination_message(void *context);

/* card_boot_release_five_message_entries.c */
void card_boot_release_five_message_entries(void *record);

/* card_boot_release_three_row_panel_text.c */
void card_boot_release_three_row_panel_text(void *record);

/* card_boot_stop_slot_window_updates.c */
void card_boot_stop_slot_window_updates(void *record_data);

/* format_save_heading_text.c */
void format_save_heading_text(s32 base_addr);

/* initialize_text_editor_context.c */
void initialize_text_editor_context(void *dest, s32 record_index);

/* release_three_row_panel_text.c */
void release_three_row_panel_text(struct S_8002742C_0 *object);

/* write_text_and_advance_selection.c */
void write_text_and_advance_selection(u8 *menu);

#endif
