#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x37: Copy variable with operands swapped: v[dst] = v[src], src first. */
void script_copy_variable_reversed(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 source;
    u8 destination;

    source = *cursor++;
    window->cursor = cursor;
    destination = *cursor++;
    window->cursor = cursor;

    window->controller->variables[destination] = window->controller->variables[source];
}
