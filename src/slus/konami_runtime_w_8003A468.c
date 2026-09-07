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

void func_8003A468(RuntimeState *state)
{
    u32 cursor;
    u32 lhs;
    u32 rhs;

    cursor = (u32)state->read_ptr;
    lhs = *(u8 *)cursor;
    cursor++;
    state->read_ptr = (u8 *)cursor;
    rhs = *(u8 *)cursor;
    cursor++;
    state->read_ptr = (u8 *)cursor;

    state->table->values[lhs] += state->table->values[rhs];
}
