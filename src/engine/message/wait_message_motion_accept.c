#include "engine/message.h"

/* ms_mot_accpt_ow: advance the state handler when the state check succeeds or the countdown expires. */
void wait_message_motion_accept(MessageWindow *window) {
    if (ms_mot_accpt_ow(window->entry_index) == 0) {
        window->motion_timer -= 1;
        if (window->motion_timer >= 0) {
            return;
        }
    }
    window->message_handler = update_message_window;
}
