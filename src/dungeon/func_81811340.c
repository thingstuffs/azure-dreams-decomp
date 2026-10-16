#include "modules/dungeon_ovl_1830850.h"

void inventorySetEmbeddedStateFour(s32 object_addr) {
    ovl_1830850_81811340_S_80026340_0 *state;

    state = object_addr + 0x20;
    state->unk_08 = 4;
    inventorySetPairedIndexOffset(state->unk_54, 4);
}
