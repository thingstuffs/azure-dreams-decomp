#ifndef TOWN_SCENE_DIALOGUE_H
#define TOWN_SCENE_DIALOGUE_H
/* Prototypes of the functions defined in src/town/scene/dialogue/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* advance_delayed_panel_line.c */
void advance_delayed_panel_line(void *ptr);

/* append_string.c */
u8 *append_string(u8 *dst, u8 *src);

/* build_visible_item_line_packets.c */
s32 build_visible_item_line_packets(void *first_item);

/* copy_string.c */
u8 *copy_string(u8 *destination, u8 *source);

/* start_event_message.c */
s32 start_event_message(void);

/* install_scene_handler_and_close_dialogue.c */
s32 func_8001781C(void);
s32 install_scene_handler_and_close_dialogue(void);

/* install_scene_handler_and_close_dialogue_second.c */
void *select_response_if_entry_flag_set(void *context, s32 unused, s32 mode);

/* prepare_shared_text_buffer.c */
void *prepare_shared_text_buffer(s32 source);

/* report_scene_busy_until_message_closes.c */
s32 report_scene_busy_until_message_closes(void);

/* select_dialogue_with_override.c */
s32 select_dialogue_with_flag_override(s32 speaker, s32 interaction, s32 dialogue_id);

/* select_text_by_current_message.c */
u8 *select_text_by_current_message(void);

/* select_next_dialogue_line.c */
s8 *select_next_dialogue_line(void);

/* select_message_text_marking_pad08.c */
char *select_message_text_marking_pad08(s32 unused_0, s32 unused_1, s32 selector);

/* process_entry_or_start_message.c */
s32 process_entry_or_start_message(void *object, s32 entry_index);


typedef struct {
    u8 character;
    u8 field1;
    u8 field2;
    u8 field3;
} DialogueTextCell;

#endif
