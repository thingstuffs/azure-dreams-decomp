#include "slus/owned_80038A10.h"

void func_80038A10(Func80038A10State *input_state) {
    Func80038A10State *state = input_state;
    GameWork *global = &gameWork;
    void *context = input_state->field80;
    void (*handler)(Func80038A10State *);

    D_80081448 = state;

    if (state->field87 == 0) {
        if ((((u32)global->buttons) & 0x20) != 0) {
            if (state->field2E == 0) {
                state->field2E = 1;
            }
        }
    }

    handler = func_80038A10;

    do {
        if (func_80038AB8((struct RuntimeContext *)state, (u8 *)context) == 0) {
            break;
        }
    } while (state->func10 == handler);
}
