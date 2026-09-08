#include "common.h"

typedef struct Func8003A01CState Func8003A01CState;

typedef struct {
    u8 pad00[0x1c];
    u8 *cursor;
    u8 pad20[0x60];
    Func8003A01CState *state;
} Func8003A01CContext;

struct Func8003A01CState {
    u8 pad00[0x44];
    u32 **table;
    u32 values[256];
};

/* Handles event-script opcode 53 by copying an indirect table value into the selected VM value slot. */
void func_8003A01C(Func8003A01CContext *context) {
    u8 *cursor = context->cursor;
    Func8003A01CState *state = context->state;
    u8 value_index;
    u8 table_index;

    value_index = *cursor++;
    context->cursor = cursor;
    table_index = *cursor++;
    context->cursor = cursor;
    state->values[value_index] = **(state->table + table_index);
}
