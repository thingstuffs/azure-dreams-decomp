#include "engine/message.h"
#include "slus.h"

/* Selects the next handler based on runtime status and the context byte. */
MessageWindowHandler select_message_wait_handler(MessageWindow *window) {
    if (read_sound_mode_blocking_status(4) != 0x100) {
        if (play_message_confirmation_sound(*window->cursor) != 0) {
            return finish_message_when_idle;
        }
        return start_message_countdown;
    }
    return choose_message_wait_handler;
}
