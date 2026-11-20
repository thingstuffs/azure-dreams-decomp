#include "engine/message.h"
#include "engine/script.h"

/* Opcode 0x27: Poll handler [group][entry] (two u8) until it returns nonzero. */
void script_poll_group_handler(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 value = *cursor++;

    window->cursor = cursor;
    window->service_index = value;
    value = *cursor++;
    window->cursor = cursor;
    window->message_handler = run_message_table_handler;
    window->service_entry = value;
}
