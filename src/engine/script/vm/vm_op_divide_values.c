#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x4A: v[dst] /= v[src]. */
s32 script_divide(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 dst = *cursor++;
    u8 src;
    ScriptController *controller;

    window->cursor = cursor;
    src = *cursor++;
    window->cursor = cursor;
    controller = window->controller;
    return controller->variables[dst] /= controller->variables[src];
}
