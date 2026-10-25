#ifndef DUNGEON_ITEM_MESSAGE_H
#define DUNGEON_ITEM_MESSAGE_H

#include "common.h"

void *get_unused_text_buffer(void);
u8 *expand_text_control_codes(const u8 *source, u8 *buffer);
void *clear_byte_and_advance(s8 *byte_ptr);
u8 *append_entity_display_text(void *record, u8 *buffer);
void display_formatted_context_message(void *source);
void adjust_source_value_and_finalize(void *context, const void *source);

#endif
