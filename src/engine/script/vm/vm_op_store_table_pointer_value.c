#include "engine/script/vm.h"
#include "engine/message.h"

void script_store_system_variable(MessageWindow *window) {
    u8 *cursor = window->cursor;
    ScriptController *controller = window->controller;
    u8 value_index;
    u8 address_index;
    s32 *word;

    value_index = *cursor++;
    window->cursor = cursor;
    address_index = *cursor++;
    window->cursor = cursor;
    word = controller->variable_addresses[address_index];
    *word = controller->variables[value_index];
}
