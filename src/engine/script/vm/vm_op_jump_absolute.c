#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x17 jumps to the absolute script address. */
void script_jump(MessageWindow *window) {
    u8 *operand = window->cursor;

    window->cursor = read_script_address(operand);
}
