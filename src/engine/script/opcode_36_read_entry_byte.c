#include "engine/message.h"
#include "engine/script.h"

/* Opcode 0x24: Wait until the u8 actor entry is ready. */
void script_wait_actor_ready(MessageWindow *window) {
    u8 *stream = window->cursor;
    u8 value = *stream;

    window->cursor = stream + 1;
    window->message_handler = wait_message_entry_ready;
    window->entry_index = value;
}
