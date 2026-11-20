#include "engine/message.h"

/* Decrements the countdown and switches the handler when the signed count reaches zero or below. */
void decrement_countdown_and_switch(MessageWindow *window) {
    if (--window->countdown <= 0) {
        window->message_handler = update_message_window;
    }
}
