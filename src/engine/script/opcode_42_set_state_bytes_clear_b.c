#include "common.h"
#include "engine/message/state.h"
#include "engine/script.h"

struct S_800385D0_0;

typedef struct Func80039C44State {
    u8 pad_00[0x10];
    void (*func_10)(struct S_800385D0_0 *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x06];
    u8 byte_26;
    u8 byte_27;
} Func80039C44State;

/* Opcode 0x2A: Timed choice menu with u8 options. */
void script_timed_choice_menu(Func80039C44State *state) {
    u32 operand = (u32)state->read_ptr;
    u32 read_addr = operand;

    operand = *(u8 *)operand;
    state->read_ptr = (u8 *)(read_addr + 1);
    state->byte_27 = 0;
    state->func_10 = clear_two_state_fields_b;
    state->byte_26 = (u8)operand;
}
