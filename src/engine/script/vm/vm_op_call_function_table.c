#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x2E calls the numbered service with variables 0 through 3. */
void script_call_service(MessageWindow *window) {
    u8 *cursor = window->cursor;
    ScriptController *controller = window->controller;
    u8 index = *cursor;
    MessageServiceHandler *handlers = controller->service_handlers;

    window->cursor = cursor + 1;
    controller->variables[15] = handlers[index](
        controller->variables[0], controller->variables[1],
        controller->variables[2], controller->variables[3]);
}
