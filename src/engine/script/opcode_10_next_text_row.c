#include "engine/message.h"
#include "engine/script.h"

/* Opcode 0x0A: New line: move to the next text row, scrolling when the window is full. */
void script_new_line(MessageWindow *window) {
    window->column = 0;
    if (window->row < window->row_count - 1) {
        window->row++;
        if (window->text_advance_mode == 1) {
            window->countdown = 0;
            window->message_handler = decrement_countdown_and_switch;
        }
    } else {
        window->message_handler = scroll_message_rows;
    }
}
