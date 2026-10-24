#include "common.h"

#include "common.h"
#include "engine/message/state.h"
#include "engine/script.h"

typedef struct Func80039730State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x06];
    u8 byte_26;
    u8 byte_27;
} Func80039730State;

/* Opcode 0x19: Choice menu with u8 options; the answer goes to +0x27. */
void script_choice_menu(Func80039730State *state) {
    u32 operand = (u32)state->read_ptr;
    u32 read_addr = operand;

    operand = *(u8 *)operand;
    state->read_ptr = (u8 *)(read_addr + 1);
    state->byte_27 = 0;
    state->func_10 = clear_two_state_fields;
    state->byte_26 = (u8)operand;
}
