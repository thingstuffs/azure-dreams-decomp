#include "engine/message.h"
#include "engine/script.h"

/* Opcode 0x25: Poll call number u8 with v0..v3 every frame until it returns nonzero (result to v15). */
void script_poll_service(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 value = *cursor;

    window->cursor = cursor + 1;
    window->message_handler = run_message_opcode_handler;
    window->service_index = value;
}
