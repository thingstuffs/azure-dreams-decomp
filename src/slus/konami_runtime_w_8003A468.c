#include "common.h"

typedef struct ValueTable {
    u8 pad_00[0x48];
    s32 values[1];
} ValueTable;

typedef struct RuntimeState {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    ValueTable *table;
} RuntimeState;

/* Adds one event-script variable to another. */
void func_8003A468(RuntimeState *state)
{
    u32 script_cursor;
    u32 dest_index;
    u32 source_index;

    script_cursor = (u32)state->read_ptr;
    dest_index = *(u8 *)script_cursor;
    script_cursor++;
    state->read_ptr = (u8 *)script_cursor;
    source_index = *(u8 *)script_cursor;
    script_cursor++;
    state->read_ptr = (u8 *)script_cursor;

    state->table->values[dest_index] += state->table->values[source_index];
}
