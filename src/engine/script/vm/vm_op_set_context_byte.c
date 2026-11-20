#include "engine/message.h"
#include "engine/script/vm.h"

/* Opcode 0x09: Set the text speed (the signed rate used by the glyph renderer). */
void script_set_text_speed(MessageWindow *window) {
    u8 *script_ptr = window->cursor;
    u8 value = *script_ptr;

    script_ptr++;
    window->cursor = script_ptr;
    window->text_speed = value;
}
