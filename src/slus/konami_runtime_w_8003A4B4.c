#include "common.h"

typedef struct Func8003A4B4Entry {
    u8 pad_00[0x48];
    s32 value[256];
} Func8003A4B4Entry;

typedef struct Func8003A4B4State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Func8003A4B4Entry *table;
} Func8003A4B4State;

/* Subtracts one event-script variable from another. */
void func_8003A4B4(Func8003A4B4State *state) {
    u8 *script_cursor;
    s32 dest_index;
    s32 source_index;
    Func8003A4B4Entry *table;

    script_cursor = state->read_ptr;
    dest_index = *script_cursor;
    script_cursor++;
    state->read_ptr = script_cursor;
    source_index = *script_cursor;
    script_cursor++;
    state->read_ptr = script_cursor;

    table = state->table;
    table->value[dest_index] = table->value[dest_index] - table->value[source_index];
}
