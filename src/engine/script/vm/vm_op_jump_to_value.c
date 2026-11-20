#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x48 jumps to the PS1 address stored in the selected variable. */
void script_jump_to_variable(MessageWindow *window) {
    u8 index = *window->cursor++;

    window->cursor = script_address_from_word(window->controller->variables[index]);
}
