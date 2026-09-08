#include "common.h"

typedef struct Func8003A29CTable {
    u8 pad_00[0x44];
    u32 **targets;
    u32 values[1];
} Func8003A29CTable;

typedef struct Func8003A29CState {
    u8 pad_00[0x1C];
    u8 *cursor;
    u8 pad_20[0x60];
    Func8003A29CTable *table;
} Func8003A29CState;

/* Copies a script-selected table value to a script-selected target. */
void func_8003A29C(Func8003A29CState *state) {
    u8 *cursor = state->cursor;
    u8 value_index;
    u8 target_index;
    Func8003A29CTable *table = state->table;

    value_index = *cursor++;
    state->cursor = cursor;
    target_index = *cursor++;
    state->cursor = cursor;
    table->targets[target_index][0] = table->values[value_index];
}
