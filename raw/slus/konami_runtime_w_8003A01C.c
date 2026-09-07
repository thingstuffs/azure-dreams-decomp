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

void func_8003A01C(Func8003A01CContext *arg0) {
    u8 *cursor = arg0->cursor;
    Func8003A01CState *state = arg0->state;
    u8 first;
    u8 second;

    first = *cursor++;
    arg0->cursor = cursor;
    second = *cursor++;
    arg0->cursor = cursor;
    state->values[first] = **(state->table + second);
}
