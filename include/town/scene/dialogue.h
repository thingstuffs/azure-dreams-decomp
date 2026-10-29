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

/* dispatch_enabled_message_coordinates.c */
s32 dispatch_enabled_message_coordinates(void);

/* install_scene_handler_and_close_dialogue.c */
s32 func_8001781C(void);
s32 install_scene_handler_and_close_dialogue(void);

/* install_scene_handler_and_close_dialogue_second.c */
void *select_checked_table_pointer(void *context, s32 unused, s32 mode);

/* prepare_shared_text_buffer.c */
void *prepare_shared_text_buffer(s32 source);

/* report_scene_busy_until_message_closes.c */
s32 report_scene_busy_until_message_closes(void);

/* select_dialogue_with_override.c */
s32 select_dialogue_with_799_override(s32 speaker, s32 interaction, s32 dialogue_id);

/* select_message_based_message_callback.c */
u8 *select_message_based_message_callback(void);

/* select_next_dialogue_line.c */
s8 *select_next_dialogue_line(void);

/* select_string_performs_any_associated.c */
char *select_string_performs_any_associated(s32 unused_0, s32 unused_1, s32 selector);

/* wait_for_dialogue_then_close.c */
s32 wait_for_dialogue_then_close(void *object, s32 entry_index);

#endif
