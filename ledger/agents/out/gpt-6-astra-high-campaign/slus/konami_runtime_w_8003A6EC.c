#include "common.h"

#include "common.h"

typedef struct Func8003A6ECEntry {
    u8 pad_00[0x48];
    s32 value;
} Func8003A6ECEntry;

typedef struct Func8003A6ECState {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A6ECState *table;
} Func8003A6ECState;

/* Jumps to the encoded address if the indexed table value is nonnegative, otherwise skips it. */
void func_8003A6EC(Func8003A6ECState *state) {
    u8 *stream_ptr = state->read_ptr;
    u8 table_index = *stream_ptr;

    stream_ptr++;
    state->read_ptr = stream_ptr;

    if (((Func8003A6ECEntry *)((u8 *)state->table + table_index * 4))->value >= 0) {
        u32 jump_address = (u32)stream_ptr[0]
                         + ((u32)stream_ptr[1] << 8)
                         + ((u32)stream_ptr[2] << 16)
                         + ((u32)stream_ptr[3] << 24);
        state->read_ptr = (u8 *)jump_address;
    } else {
        state->read_ptr = stream_ptr + 4;
    }
}
