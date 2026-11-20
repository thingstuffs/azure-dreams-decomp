#include "engine/script/vm.h"
#include "engine/message.h"

/* Opcode 0x3D: Compare: v15 = v[a] - v[b]. */
void script_compare(MessageWindow *window) {
    u8 *cursor = window->cursor;
    u8 left = *cursor++;
    u8 right;
    ScriptController *controller;

    window->cursor = cursor;
    right = *cursor++;
    window->cursor = cursor;
    controller = window->controller;
    controller->variables[15] = controller->variables[left] - controller->variables[right];
}
