#ifndef DUNGEON_ITEM_MESSAGE_H
#define DUNGEON_ITEM_MESSAGE_H

#include "common.h"
#include "shared/dungeon_item_entries.h"

void *get_unused_text_buffer(); /* Unprototyped: retail callers forward varying ignored arguments; incoming values are replaced. */
u8 *expand_text_control_codes(const u8 *source, u8 *buffer);
u8 *clear_byte_and_advance(u8 *byte_ptr);
u8 *append_entity_display_text(void *record, u8 *buffer);
void display_formatted_context_message(void *source);
void adjust_source_value_and_finalize(void *context, const void *source);

u8 *write_text_byte_and_advance(s8 value, u8 *dest);

u8 *append_typed_formatted_value(DungeonItemEntry *data, u8 *buffer);

void *copy_four_text_bytes(u8 *source, u8 *buffer);

#endif
