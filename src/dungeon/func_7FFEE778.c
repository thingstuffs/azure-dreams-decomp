#include "modules/dungeon_town_map.h"

void restore_town_map_input_state(town_map_7FFEE778_S_8008BED8_0 *state) {
    M2C_UNK *handler;
    u32 status = D_800FC418;

    if (status == 0xFF) {
        handler = (M2C_UNK *)advance_town_map_countdown_callback;
    } else if (status == 0) {
        handler = (M2C_UNK *)handle_town_map_input;
    } else {
        return;
    }
    state->unk_68 = handler;
}
