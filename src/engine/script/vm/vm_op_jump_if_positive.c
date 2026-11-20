#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x43: If v[var] > 0, jump to the 32-bit address. */
void script_jump_if_positive(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 index = *cursor++;

    window->cursor = cursor;
    if (window->controller->variables[index] > 0) {
        window->cursor = read_script_address(cursor);
    } else {
        window->cursor = cursor + 4;
    }
}
