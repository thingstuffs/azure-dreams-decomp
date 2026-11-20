#include "engine/script.h"
#include "engine/message.h"

/* Opcode 0x33: Copy variable: v[dst] = v[src]. */
void script_copy_variable_a(MessageWindow *window) {
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
