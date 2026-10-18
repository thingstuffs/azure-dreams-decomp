#include "modules/dungeon_ovl_1831cd8.h"

void clear_menu_embedded_state(s32 object_addr) {
    ovl_1831cd8_81813620_S_80028620_0 *state;

    state = object_addr + 0x20;
    state->unk_20 = 0;
    clear_menu_state_values(state->unk_88);
}
