#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x4B saves the continuation and calls the address in the selected variable. */
void script_call_variable(MessageWindow *window) {
    ScriptController *controller = window->controller;
    u8 index = *window->cursor++;

    *window->returns.next = window->cursor;
    window->returns.next++;
    window->cursor = script_address_from_word(controller->variables[index]);
}
