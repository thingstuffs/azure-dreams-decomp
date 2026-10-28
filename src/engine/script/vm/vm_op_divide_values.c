#include "common.h"
#include "engine/script/vm.h"

typedef struct {
    u8 pad_00[0x48];
    s32 values[256];
} Table;

typedef struct Func8003A904State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    Table *table;
} Func8003A904State;

/* Opcode 0x4A: v[dst] /= v[src]. */
s32 script_divide(Func8003A904State *script) {
    u8 *read_ptr = script->read_ptr;
    u8 left_index;
    u8 right_index;
    s32 quotient;

    left_index = *read_ptr;
    read_ptr += 1;
    script->read_ptr = read_ptr;
    right_index = *read_ptr;
    read_ptr += 1;
    script->read_ptr = read_ptr;
    quotient = script->table->values[left_index] / script->table->values[right_index];
    script->table->values[left_index] = quotient;
    return quotient;
}
