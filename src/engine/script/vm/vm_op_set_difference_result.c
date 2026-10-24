#include "common.h"
#include "engine/script/vm.h"

typedef struct Func8003A500Entry {
    u8 pad_00[0x48];
    s32 value;
} Func8003A500Entry;

typedef struct Func8003A500State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A500State *table;
    s32 result;
} Func8003A500State;

/* Opcode 0x3D: Compare: v15 = v[a] - v[b]. */
void script_compare(Func8003A500State *state) {
    u8 *script_cursor = state->read_ptr;
    u8 lhs_index = *script_cursor;
    u8 rhs_index;
    script_cursor++;
    state->read_ptr = script_cursor;
    rhs_index = *script_cursor;
    script_cursor++;
    state->read_ptr = script_cursor;

    state = state->table;
    state->result = ((Func8003A500Entry *)((u8 *)state + lhs_index * 4))->value
    - ((Func8003A500Entry *)((u8 *)state + rhs_index * 4))->value;
}
