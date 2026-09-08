#include "common.h"

#include "common.h"

typedef struct Func8003A7FCTable {
    u8 pad_00[0x48];
    u32 values[256];
} Func8003A7FCTable;

typedef struct Func8003A7FCState {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func8003A7FCTable *table;
} Func8003A7FCState;

/* Stores a little-endian 32-bit script operand in the indexed VM table entry. */
void func_8003A7FC(Func8003A7FCState *state) {
    u8 *cursor = state->read_ptr;
    Func8003A7FCTable *table = state->table;
    u8 index = *cursor++;

    state->read_ptr = cursor;
    table->values[index] = cursor[0] + (cursor[1] << 8) +
                           (cursor[2] << 16) + (cursor[3] << 24);

    state->read_ptr += 4;
}
