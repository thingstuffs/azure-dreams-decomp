#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x0B displays the remaining text immediately. */
void script_instant_text(MessageWindow *window) {
    window->text_advance_mode = 2;
}
