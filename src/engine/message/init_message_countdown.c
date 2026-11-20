#include "engine/message.h"

/* Initialize the context and set its next handler and state. */
void start_message_countdown(MessageWindow *window) {
    read_message_byte(window);
    window->countdown = 5;
    window->message_handler = decrement_countdown_and_switch_b;
}
