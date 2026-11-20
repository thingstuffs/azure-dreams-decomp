#include "slus.h"
#include "engine/message.h"
#include "shared/game_work.h"

/* Latches the message button and runs script actions until the window handler changes or execution stops. */
void update_message_window(MessageWindow *window) {
    GameWork *global = &g_game_work;
    ScriptController *controller = window->controller;
    MessageWindowHandler handler;

    current_message_window_state = window;

    if (window->skip_disabled == 0) {
        if ((((u32)global->buttons) & 0x20) != 0) {
            if (window->text_advance_mode == 0) {
                window->text_advance_mode = 1;
            }
        }
    }

    handler = update_message_window;

    do {
        if (interpret_script_opcodes(window, controller) == 0) {
            break;
        }
    } while (window->message_handler == handler);
}
MessageWindow *current_message_window_state = 0;
