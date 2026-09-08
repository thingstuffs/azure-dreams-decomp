#include "common.h"

typedef struct Func8003A54CEntry {
    u8 pad_00[0x48];
    u32 value;
} Func8003A54CEntry;

typedef struct Func8003A54CState {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A54CState *table;
} Func8003A54CState;

// Jump to the encoded address if the indexed table value is zero; otherwise skip it.
void func_8003A54C(Func8003A54CState *state) {
    u8 *stream_cursor = state->read_ptr;
    u8 table_index = *stream_cursor;

    stream_cursor++;
    state->read_ptr = stream_cursor;

    if (((Func8003A54CEntry *)((u8 *)state->table + table_index * 4))->value == 0) {
        u32 jump_address = (u32)stream_cursor[0]
                         + ((u32)stream_cursor[1] << 8)
                         + ((u32)stream_cursor[2] << 16)
                         + ((u32)stream_cursor[3] << 24);
        state->read_ptr = (u8 *)jump_address;
    } else {
        state->read_ptr = stream_cursor + 4;
    }
}
