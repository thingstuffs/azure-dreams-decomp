#include "modules/dungeon_ovl_16b08_local.h"

void func_80094620(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context) {
    townCallTheHandlerSelectsNonzeroEntry(D_800D0148, state, context);
    state->callback = (void *)townUpdateThresholdObjectWithInteraction;
}
