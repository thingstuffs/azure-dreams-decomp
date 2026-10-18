#include "modules/dungeon_ovl_1831cd8.h"

void run_menu_countdown_callback(s32 *state) {
    D_8002952C[state[5]](state);
    state[0]--;
    if (state[0] < 0) {
        state[0] = 0;
        dispatch_menu_state_update((u8 *)state + 0x38, state[5], (state[2] / 72) * 72, state[10]);
        state[-4] = (u32)(void *)dispatch_menu_update_callback;
    }
    invoke_enabled_menu_callback(state);
}
