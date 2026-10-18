#include "modules/dungeon_ovl_1831cd8.h"

void dispatch_menu_update_callback(s32 *state) {
    D_8002951C[state[5]](state);
    state[0]++;
    if (state[1] < state[0]) {
        set_entry_destination_and_value(state[34], state[19]);
        position_menu_grid_entries(state[34], state[2]);
        state[-4] = (u32)(void *)handle_menu_record_check;
    }
    invoke_enabled_menu_callback(state);
}
