#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x15 saves the continuation and calls the absolute script address. */
void script_call(MessageWindow *window) {
    u8 *operand;

    *window->returns.next = window->cursor + 4;
    operand = window->cursor;
    window->returns.next++;
    window->cursor = read_script_address(operand);
}
