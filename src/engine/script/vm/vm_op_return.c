#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x16 and a zero text byte both return to the saved cursor. */
void script_return(MessageWindow *window) {
    window->cursor = *--window->returns.next;
}
