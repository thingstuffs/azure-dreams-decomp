#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x32: Fill v0..v15 with the u8 operand. */
void script_fill_variables(MessageWindow *window) {
    u8 *cursor = window->cursor;
    ScriptController *controller = window->controller;
    s32 entry_index;
    s32 fill_value = *cursor;

    cursor++;
    window->cursor = cursor;
    entry_index = 15;
    do {
        controller->variables[entry_index] = fill_value;
        entry_index--;
    } while (entry_index >= 0);
}
