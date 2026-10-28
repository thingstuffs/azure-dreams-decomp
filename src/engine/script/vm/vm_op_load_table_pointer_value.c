#include "common.h"
#include "engine/script/vm.h"

typedef struct Func8003A01CState Func8003A01CState;

typedef struct Func8003A01CContext {
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

/* Opcode 0x35: Load system variable: v[var] = *S_ARG[u8] (pointer table at VM block +0x44). */
void script_load_system_variable(Func8003A01CContext *context) {
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
