#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x05 copies one operand into the controller. */
void script_store_block_byte(MessageWindow *window) {
    u8 *cursor = window->cursor;

    window->controller->field3D = *cursor;
    window->cursor = cursor + 1;
}
