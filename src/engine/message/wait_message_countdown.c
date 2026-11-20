#include "engine/message.h"
#include "shared/game_work.h"

/* Advance to the next handler when the countdown expires or the global flag permits. */
void wait_message_countdown(MessageWindow *window) {
    GameWork *global = &g_game_work;

    if (window->skip_disabled == 0) {
        if ((((u32)global->buttons) & 0x20) != 0) {
            if (window->text_advance_mode == 0) {
                window->text_advance_mode = 1;
            }
            window->countdown = 0;
            window->message_handler = update_message_window;
            return;
        }
    }

    window->countdown -= 1;
    if (window->countdown <= 0) {
        window->message_handler = update_message_window;
    }
}
