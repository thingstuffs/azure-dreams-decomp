#ifndef DUNGEON_ITEM_MESSAGE_TEXT_H
#define DUNGEON_ITEM_MESSAGE_TEXT_H

#include "common.h"
#include "shared/dungeon_item_entries.h"

u8 *expand_text_control_codes(const u8 *source, u8 *buffer);
u8 *copy_selected_text_without_terminator(void *text_id, u8 *dest);
u8 *clear_byte_and_advance(u8 *byte_ptr);
u8 *append_entity_display_text(void *record, u8 *buffer);
void display_formatted_context_message(void *source);

u8 *write_text_byte_and_advance(s8 value, u8 *dest);

u8 *append_typed_formatted_value(DungeonItemEntry *data, u8 *buffer);

void *copy_four_text_bytes(u8 *source, u8 *buffer);

#endif
