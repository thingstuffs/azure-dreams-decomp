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

/* Advances the sub-timer at +0x58, resetting the state to func_800504B4 once
 * the internal counter reaches 3, then always invokes func_800504B4. */
void func_800505BC(S_800505BC *arg0, s32 arg1, s32 arg2) {
    arg0->counter += 1;
    func_80050550(&arg0->unk58, arg0->counter, 3);

    if (arg0->counter >= 3) {
        arg0->counter = 0;
        arg0->func = func_800504B4;
    }

    func_800504B4(arg0, arg1, arg2);
}
