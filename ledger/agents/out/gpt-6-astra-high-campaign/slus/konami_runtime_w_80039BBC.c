#include "common.h"

typedef struct {
    u8 unk00[0x10];
    void (*handler)(void);
    u8 unk14[0x08];
    u8 *cursor;
    u8 unk20[0x12];
    u8 value;
} FuncState;

extern void func_80038690(void);

/* Read a script byte into the state value and select func_80038690 as the next handler. */
void func_80039BBC(FuncState *state) {
    u8 *cursor = state->cursor;
    u8 value = *cursor;

    state->cursor = cursor + 1;
    state->handler = func_80038690;
    state->value = value;
}
