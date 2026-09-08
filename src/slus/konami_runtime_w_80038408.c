#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x10];
    void (*state_func)(void);
    u8 pad_14[0x1B];
    u8 state_2f;
    u8 pad_30[0x59];
    u8 state_89;
} FuncState;

extern int func_800392A4(u8 arg0);
extern void func_80038A10(void);

/* Advance the state handler when the state check succeeds or the countdown expires. */
void func_80038408(FuncState *state) {
    if (func_800392A4(state->state_2f) == 0) {
        state->state_89 -= 1;
        if ((signed char)state->state_89 >= 0) {
            return;
        }
    }
    state->state_func = func_80038A10;
}
