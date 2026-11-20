#include "engine/message.h"
#include "slus.h"

/* Call the handler when check 4 returns zero. */
void finish_message_when_idle(MessageWindow *window) {
    if (read_sound_mode_blocking_status(4) == 0) {
        start_message_countdown(window);
    }
}
