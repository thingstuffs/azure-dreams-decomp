#include "modules/dungeon_ovl_1830850.h"

void inventory_set_embedded_state_four(s32 object_addr) {
    ovl_1830850_81811340_S_80026340_0 *state;

    state = object_addr + 0x20;
    state->unk_08 = 4;
    inventory_set_paired_index_offset(state->unk_54, 4);
}
