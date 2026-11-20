#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x57: Page break: wait for a button; the next byte is then read as the wait mode. */
void script_page_break(MessageWindow *window) {
    window->message_handler = noop_script_terminator_action;
    window->cursor--;
}
