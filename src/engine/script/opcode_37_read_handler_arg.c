#include "common.h"

typedef struct {
    u8 unk00[0x10];
    void (*handler)(void);
    u8 unk14[0x08];
    u8 *cursor;
    u8 unk20[0x12];
    u8 value;
} FuncState;

extern void run_message_opcode_handler(void);

/* Read a script byte into the state value and select run_message_opcode_handler as the next handler. */
void handle_vm_opcode_37(FuncState *state) {
    u8 *cursor = state->cursor;
    u8 value = *cursor;

    state->cursor = cursor + 1;
    state->handler = run_message_opcode_handler;
    state->value = value;
}
