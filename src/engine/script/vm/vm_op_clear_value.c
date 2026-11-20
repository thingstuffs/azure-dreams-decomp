#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x31 clears the variable selected by its byte operand. */
void script_clear_variable(MessageWindow *window) {
    u8 *cursor = window->cursor;

    window->controller->variables[*cursor] = 0;
    window->cursor = cursor + 1;
}
