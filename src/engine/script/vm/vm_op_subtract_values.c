#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x3C: v[dst] -= v[src]. */
void script_subtract(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 dst = *cursor++;
    u8 src;
    ScriptController *controller;

    window->cursor = cursor;
    src = *cursor++;
    window->cursor = cursor;
    controller = window->controller;
    controller->variables[dst] -= controller->variables[src];
}
