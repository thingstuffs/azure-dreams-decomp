#include "modules/dungeon_ovl_1831cd8.h"

void func_80027D7C(s32 *state) {
    D_8002951C[state[5]](state);
    state[0]++;
    if (state[1] < state[0]) {
        func_80026CF0(state[34], state[19]);
        func_80026D0C(state[34], state[2]);
        state[-4] = (u32)(void *)func_80027A88;
    }
    func_80027A20(state);
}
