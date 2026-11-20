#include "engine/script.h"
#include "engine/message.h"

/* Opcode 0x44: Copy variable: v[dst] = v[src] (same as opcode 0x33). */
void script_copy_variable_b(MessageWindow *window) {
    u8 *script_ptr = window->cursor;
    u8 destination;
    u8 source;

    destination = *script_ptr;
    script_ptr += 1;
    window->cursor = script_ptr;
    source = *script_ptr;
    script_ptr += 1;
    window->cursor = script_ptr;
    window->controller->variables[destination] = window->controller->variables[source];
}
