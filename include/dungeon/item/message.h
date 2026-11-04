#ifndef DUNGEON_ITEM_MESSAGE_H
#define DUNGEON_ITEM_MESSAGE_H

#include "dungeon/item/message/text.h"

void *get_unused_text_buffer(void);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void display_formatted_context_message(void *context);

#endif
