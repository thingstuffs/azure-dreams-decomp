#include "common.h"

typedef struct {
    u8 pad[0x48];
    u32 values[256];
} Table;

typedef struct Func80039F80State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Table *table;
} Func80039F80State;

/* Opcode 0x33: Copy variable: v[dst] = v[src]. */
void script_copy_variable_a(Func80039F80State *reader) {
    u8 *script_ptr = reader->read_ptr;
    u8 destination;
    u8 source;

    destination = *script_ptr;
    script_ptr += 1;
    reader->read_ptr = script_ptr;
    source = *script_ptr;
    script_ptr += 1;
    reader->read_ptr = script_ptr;
    reader->table->values[destination] = reader->table->values[source];
}
