#include "modules/dungeon_ovl_1830850.h"

void inventorySetEmbeddedStateOne(s32 object_addr) {
    ovl_1830850_81811314_S_80026314_0 *state;

    state = object_addr + 0x20;
    state->unk_10 = 1;
    dungeonSetDestinationBytePointer(state->unk_54);
}
