#include "common.h"

#include "common.h"

typedef struct Func80038A10State Func80038A10State;

struct Func80038A10State {
    u8 pad0[0x10];
    void (*func10)(Func80038A10State *);
    u8 pad14[0x1A];
    u8 field2E;
    u8 pad2F[0x51];
    void *field80;
    u8 pad84[3];
    s8 field87;
};

typedef struct {
    u8 pad0[8];
    u32 field8;
} Func80038A10Global;

extern Func80038A10Global D_80083160;
extern Func80038A10State *D_80081448;
extern s32 func_80038AB8(Func80038A10State *, void *);
extern void func_80038A10(Func80038A10State *);

/* Processes the current state until processing stops or its handler changes. */
void func_80038A10(Func80038A10State *input_state) {
    Func80038A10State *state = input_state;
    Func80038A10Global *global = &D_80083160;
    void *context = input_state->field80;
    void (*handler)(Func80038A10State *);

    D_80081448 = state;

    if (state->field87 == 0) {
        if ((global->field8 & 0x20) != 0) {
            if (state->field2E == 0) {
                state->field2E = 1;
            }
        }
    }

    handler = func_80038A10;

    do {
        if (func_80038AB8(state, context) == 0) {
            break;
        }
    } while (state->func10 == handler);
}
