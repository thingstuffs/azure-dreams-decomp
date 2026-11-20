#include "engine/message.h"
#include "engine/message/data.h"
#include "engine/script/vm.h"
#include "engine/town.h"

/* Processes stream control bytes until the next data byte. */
void process_message_control_bytes(MessageWindow *window) {
    ScriptController *controller;
    u32 target_ptr_addr;
    s8 signed_opcode;
    u8 opcode;
    u8 *command_ptr;
    u8 *operand_ptr;
    u8 *decimal_operand;

    opcode = *window->cursor;
    controller = window->controller;
    while ((u8)(opcode + 3) < 3U || opcode == 0) {
        command_ptr = window->cursor;
        signed_opcode = (s8)*command_ptr;
        if (signed_opcode == -3) {
            *window->returns.next = command_ptr + 2;
            decimal_operand = window->cursor;
            window->returns.next++;
            window->cursor = decimal_operand + 1;
            format_fullwidth_decimal(controller->variables[decimal_operand[1]],
                                     window->controller->decimal_text);
            window->cursor = window->controller->decimal_text;
        } else if (signed_opcode == -2) {
            *window->returns.next = command_ptr + 2;
            command_ptr = window->cursor;
            window->returns.next++;
            window->cursor = command_ptr + 1;
            window->cursor = message_control_string_table[command_ptr[1]];
        } else if (signed_opcode == -1) {
            *window->returns.next = command_ptr + 5;
            command_ptr = window->cursor;
            operand_ptr = command_ptr + 1;
            window->returns.next++;
            window->cursor = operand_ptr;
            target_ptr_addr = (u32)command_ptr[1] + ((u32)operand_ptr[1] << 8) +
                              ((u32)operand_ptr[2] << 16) + ((u32)operand_ptr[3] << 24);
            window->cursor = *(u8 **)target_ptr_addr;
        } else {
            script_return(window);
        }
        opcode = *window->cursor;
    }
}
