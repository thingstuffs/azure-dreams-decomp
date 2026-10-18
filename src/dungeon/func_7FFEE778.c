#include "modules/dungeon_town_map.h"

void restore_town_map_input_state(town_map_7FFEE778_S_8008BED8_0 *state) {
    s32 *handler;
    u32 status = D_800FC418;

    if (status == 0xFF) {
        handler = (s32 *)advance_town_map_countdown_callback;
    } else if (status == 0) {
        handler = (s32 *)handle_town_map_input;
    } else {
        return;
    }
    state->unk_68 = handler;
}
