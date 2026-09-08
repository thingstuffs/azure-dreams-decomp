#include "common.h"

#include "common.h"

typedef struct Func80039FC0Table {
    u8 pad_00[0x48];
    u32 values[256];
} Func80039FC0Table;

typedef struct Func80039FC0State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func80039FC0Table *table;
} Func80039FC0State;

/* Stores a little-endian 32-bit script operand in the indexed VM table entry. */
void func_80039FC0(Func80039FC0State *state) {
    u8 *cursor = state->read_ptr;
    Func80039FC0Table *table = state->table;
    u8 index = *cursor++;

    state->read_ptr = cursor;
    table->values[index] = cursor[0] + (cursor[1] << 8) +
                           (cursor[2] << 16) + (cursor[3] << 24);

    state->read_ptr += 4;
}
