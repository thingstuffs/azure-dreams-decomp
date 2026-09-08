#include "common.h"

extern void (*D_8002951C[])(void);
extern void func_80026CF0(s32, s32);
extern void func_80026D0C(s32, s32);
extern void func_80027A20(s32 *);
extern s32 D_80027A88[];

/* Runs the selected callback and advances the state when its counter exceeds the limit. */
void func_80027D7C(s32 *state) {
    D_8002951C[state[5]]();
    state[0]++;
    if (state[1] < state[0]) {
        func_80026CF0(state[34], state[19]);
        func_80026D0C(state[34], state[2]);
        state[-4] = (u32)D_80027A88;
    }
    func_80027A20(state);
}
