#include "modules/dungeon_town_map.h"

void decrease_inner_value_and_load_indexed_state(town_map_7FFEE36C_MainStruct *state) {
    state->sub->unkA -= 0x200;
    if ((s16)state->sub->unkA < 0) {
        state->sub->unkA = 0;
        state->unk68 = (void *)handle_town_map_input;
        state->unk64 = (s8)D_800CFC70[state->unk66];
        state->unk6C = D_800CFC7C[state->unk66];
    }
}
