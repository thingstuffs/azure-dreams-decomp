#include "modules/dungeon_town_map.h"

void func_8008BED8(town_map_7FFEE778_S_8008BED8_0 *state) {
    M2C_UNK *handler;
    u32 status = D_800FC418;

    if (status == 0xFF) {
        handler = (M2C_UNK *)func_8008BA00;
    } else if (status == 0) {
        handler = (M2C_UNK *)func_8008BC58;
    } else {
        return;
    }
    state->unk_68 = handler;
}
