#include "common.h"

typedef struct Func8003A754Entry {
    u8 pad_00[0x48];
    s32 value;
} Func8003A754Entry;

typedef struct Func8003A754State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A754State *table;
} Func8003A754State;

/* Jump to the encoded address if the indexed table value is positive; otherwise skip it. */
void func_8003A754(Func8003A754State *state) {
    u8 *cursor = state->read_ptr;
    u8 table_index = *cursor;

    cursor++;
    state->read_ptr = cursor;

    if (((Func8003A754Entry *)((u8 *)state->table + table_index * 4))->value > 0) {
        u32 jump_address = (u32)cursor[0]
                         + ((u32)cursor[1] << 8)
                         + ((u32)cursor[2] << 16)
                         + ((u32)cursor[3] << 24);
        state->read_ptr = (u8 *)jump_address;
    } else {
        state->read_ptr = cursor + 4;
    }
}
