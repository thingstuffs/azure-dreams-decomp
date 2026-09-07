#include "common.h"

typedef struct Func8003A5B4Entry {
    u8 pad_00[0x48];
    u32 value;
} Func8003A5B4Entry;

typedef struct Func8003A5B4State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A5B4State *table;
} Func8003A5B4State;

// Jump to the encoded address if the selected table value is nonzero; otherwise skip it.
void func_8003A5B4(Func8003A5B4State *state) {
    u8 *command_ptr = state->read_ptr;
    u8 table_index = *command_ptr;

    command_ptr++;
    state->read_ptr = command_ptr;

    if (((Func8003A5B4Entry *)((u8 *)state->table + table_index * 4))->value != 0) {
        u32 jump_address = (u32)command_ptr[0]
                         + ((u32)command_ptr[1] << 8)
                         + ((u32)command_ptr[2] << 16)
                         + ((u32)command_ptr[3] << 24);
        state->read_ptr = (u8 *)jump_address;
    } else {
        state->read_ptr = command_ptr + 4;
    }
}
