#include "engine/script.h"
#include "engine/message.h"

/* Opcode 0x45: Set variable: v[var] = imm32 (same as opcode 0x34). */
void script_set_variable_b(MessageWindow *window) {
    u8 *cursor = window->cursor;
    ScriptController *controller = window->controller;
    u8 index = *cursor++;

    window->cursor = cursor;
    controller->variables[index] = cursor[0] + (cursor[1] << 8) +
                                (cursor[2] << 16) + ((u32)cursor[3] << 24);
    window->cursor += 4;
}
