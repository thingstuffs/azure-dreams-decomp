#include "common.h"

extern s8 func_8009FB34(u8, u8);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern void func_800A1B44(s32, s32);
extern u8 D_80082E80[];

/* Updates the default or linked state and dispatches action (3, 6). */
void func_800AA53C(u8 *context) {
    u8 *state;

    if ((context == 0) || (context[0x13] == 0)) {
        state = D_80082E80;
        __asm__ __volatile__("" : "=r"(state) : "0"(state));
        state[0x26] = func_8009FB34(state[0x24], state[0x25]);
        func_800A1B44(3, 6);
        return;
    }
    state = *(u8 **)(context - 0x14);
    state[0x26] = func_8009FB34(state[0x24], state[0x25]);
    func_800A19E4(state, context, 3, 6, context + 0x9C);
}
