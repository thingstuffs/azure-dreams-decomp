#include "modules/dungeon_ovl_16b08_local.h"

void func_800945B8(M2C_UNK **outputSlot, EntityRec *state, M2C_UNK initContext) {
    townDispatchSoundByGlobalFlag();
    state->flags14 = 0xFFEF0000;
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0140, outputSlot, initContext);
    *outputSlot = (void *)townUpdateTownObjectFromInput;
}
