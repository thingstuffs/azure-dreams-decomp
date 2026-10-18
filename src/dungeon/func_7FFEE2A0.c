#include "modules/dungeon_town_map.h"

void advance_town_map_countdown_callback(town_map_7FFEE2A0_Struct_7FFEE2A0 *state) {
    state->unk64--;
    if (state->unk64 < 0) {
        void (*next_callback)(void) = state->unk6C;
        state->unk68 = next_callback;
        next_callback();
    }
}
