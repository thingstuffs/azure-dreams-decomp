#include "common.h"

typedef struct S_800505BC S_800505BC;

struct S_800505BC {
    /* 0x00 */ void (*func)(S_800505BC *, s32, s32);
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 counter;
    /* 0x0C */ u8 pad0C[0x58 - 0x0C];
    /* 0x58 */ u8 unk58[0x68 - 0x58];
    /* 0x68 */ void *unk68;
};

extern void func_80050550(void *arg, s32 arg1, s32 arg2);
extern void func_800504B4(S_800505BC *arg0, s32 arg1, s32 arg2);

/* Advances the sub-timer, restores the callback at count three, and invokes func_800504B4. */
void func_800505BC(S_800505BC *state, s32 callback_arg1, s32 callback_arg2) {
    state->counter += 1;
    func_80050550(&state->unk58, state->counter, 3);

    if (state->counter >= 3) {
        state->counter = 0;
        state->func = func_800504B4;
    }

    func_800504B4(state, callback_arg1, callback_arg2);
}
