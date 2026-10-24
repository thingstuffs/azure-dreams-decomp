#include "common.h"
#include "engine/script/vm.h"

typedef struct Func8003AA84State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x5C];
    u8 **write_ptr;
    u8 **table;
} Func8003AA84State;

/* Opcode 0x4B: Call the script address held in v[var]. */
u8 *script_call_variable(Func8003AA84State *state) {
    u8 *read_ptr = state->read_ptr;
    u8 **table = state->table;
    u8 **return_stack = state->write_ptr;
    u8 target_index = *read_ptr++;
    u8 *target_ptr;

    state->read_ptr = read_ptr;
    *return_stack = read_ptr;
    state->write_ptr += 1;
    target_ptr = table[target_index + 18];
    state->read_ptr = target_ptr;
    return target_ptr;
}
