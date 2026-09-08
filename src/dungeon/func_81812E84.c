#include "common.h"

extern void (*D_8002952C[])(void);
extern void func_80027454(void *, s32, s32, s32);
extern void func_80027A20(s32 *);
extern s32 D_80027D7C[];

/* Run the state callback and transition when the countdown expires. */
void func_80027E84(s32 *state) {
    D_8002952C[state[5]]();
    state[0]--;
    if (state[0] < 0) {
        state[0] = 0;
        func_80027454((u8 *)state + 0x38, state[5], (state[2] / 72) * 72, state[10]);
        state[-4] = (u32)D_80027D7C;
    }
    func_80027A20(state);
}
