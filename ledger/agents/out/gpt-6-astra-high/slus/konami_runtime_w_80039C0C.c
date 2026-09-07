#include "common.h"

typedef struct {
    u8 unk00[0x10];
    void (*handler)(void);
    u8 unk14[0x08];
    u8 *cursor;
    u8 unk20[0x12];
    u8 first;
    u8 second;
} FuncState;

extern void func_8003875C(void);

/* Read two bytes into the state and set its handler to func_8003875C. */
void func_80039C0C(FuncState *state) {
    u8 *cursor = state->cursor;
    u8 value = *cursor++;

    state->cursor = cursor;
    state->first = value;
    value = *cursor++;
    state->cursor = cursor;
    state->handler = func_8003875C;
    state->second = value;
}
