#include "engine/message.h"
#include "slus.h"

/* Selects the context's next handler based on its current byte when updates are allowed. */
void choose_message_wait_handler(MessageWindow *window) {
    MessageWindowHandler next_handler;

    if (read_sound_mode_blocking_status(4) != 0x100) {
        if (play_message_confirmation_sound(*window->cursor) != 0) {
            next_handler = finish_message_when_idle;
        } else {
            next_handler = start_message_countdown;
        }
        window->message_handler = next_handler;
    }
}
