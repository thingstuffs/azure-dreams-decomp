#include "common.h"

#include "common.h"

typedef struct Func8003A248State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u32 *slots;
} Func8003A248State;

/* Opcode 0x37: Copy variable with operands swapped: v[dst] = v[src], src first. */
void script_copy_variable_reversed(Func8003A248State *state) {
    u32 source = *state->read_ptr++;
    u32 destination = *state->read_ptr++;

    state->slots[destination + 0x12] = state->slots[source + 0x12];
}
