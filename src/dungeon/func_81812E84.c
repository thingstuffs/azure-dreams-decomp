#include "modules/dungeon_ovl_1831cd8.h"

void dungeonRunMenuCountdownCallback(s32 *state) {
    D_8002952C[state[5]](state);
    state[0]--;
    if (state[0] < 0) {
        state[0] = 0;
        dungeonDispatchMenuStateUpdate((u8 *)state + 0x38, state[5], (state[2] / 72) * 72, state[10]);
        state[-4] = (u32)(void *)func_80027D7C;
    }
    dungeonInvokeEnabledMenuCallback(state);
}
