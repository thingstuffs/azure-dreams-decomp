#include "modules/dungeon_ovl_1830850.h"

void inventory_set_embedded_state_one(s32 object_addr) {
    ovl_1830850_81811314_S_80026314_0 *state;

    state = object_addr + 0x20;
    state->unk_10 = 1;
    set_destination_byte_pointer(state->unk_54);
}
