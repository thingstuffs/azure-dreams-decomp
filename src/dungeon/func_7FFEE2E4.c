#include "modules/dungeon_town_map.h"

void func_8008BA44(town_map_7FFEE2E4_S_8008BA44_0 *state) {
    town_map_7FFEE2E4_S_8008BA44_1 *object;
    town_map_7FFEE2E4_S_8008BA44_2 *checked_object;
    s32 next_value;

    object = state->unk_00;
    object->unk_0A = (u16) (object->unk_0A - 0x100);
    checked_object = state->unk_00;
    if ((s16) checked_object->unk_0A < 0) {
        checked_object->unk_0A = 0U;
        state->unk_68 = (M2C_UNK *)func_8008BC58;
        state->town_map_7FFEE2E4_unk_64.s = (s16) (s8) D_800CFC70[state->unk_66];
        next_value = D_800CFC7C[state->unk_66];
        state->town_map_7FFEE2E4_unk_64.u = 0x16;
        state->unk_6C = next_value;
    }
}
