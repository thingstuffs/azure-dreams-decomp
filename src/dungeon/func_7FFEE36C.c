#include "modules/dungeon_town_map.h"

void func_8008BACC(town_map_7FFEE36C_MainStruct *state) {
    state->sub->unkA -= 0x200;
    if ((s16)state->sub->unkA < 0) {
        state->sub->unkA = 0;
        state->unk68 = (void *)func_8008BC58;
        state->unk64 = (s8)D_800CFC70[state->unk66];
        state->unk6C = D_800CFC7C[state->unk66];
    }
}
