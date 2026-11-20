#include "engine/message.h"

/* Run the selected handler and advance the state callback on a nonzero result. */
void run_message_opcode_handler(MessageWindow *window) {
    ScriptController *controller = window->controller;
    s32 result;

    result = controller->service_handlers[window->service_index](
        controller->variables[0], controller->variables[1], controller->variables[2], controller->variables[3]);
    controller->variables[15] = result;
    if (result != 0) {
        window->service_value = result;
        window->message_handler = update_message_window;
    }
}
