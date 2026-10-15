#include "modules/dungeon_ovl_16b08_local.h"

void func_800945B8(M2C_UNK **outputSlot, EntityRec *state, M2C_UNK initContext) {
    func_800948DC();
    state->flags14 = 0xFFEF0000;
    func_80094984(&D_800D0140, outputSlot, initContext);
    *outputSlot = (void *)func_80092CD4;
}
