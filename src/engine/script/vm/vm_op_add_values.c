#include "common.h"
#include "engine/script/vm.h"

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

/* Opcode 0x3B: v[dst] += v[src]. */
void script_add(RuntimeState *state)
{
    void *script_cursor;
    u32 dest_index;
    u32 source_index;

    script_cursor = state->read_ptr;
    dest_index = *(u8 *)script_cursor;
    script_cursor++;
    state->read_ptr = script_cursor;
    source_index = *(u8 *)script_cursor;
    script_cursor++;
    state->read_ptr = script_cursor;

    state->table->values[dest_index] += state->table->values[source_index];
}
