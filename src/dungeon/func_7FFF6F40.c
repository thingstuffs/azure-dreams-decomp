#include "modules/dungeon_ovl_16b08_local.h"

void func_800946A0(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context) {
    townStoreTheValidSharedAngleInOffsetHex10(state, argument, context);
    townCallTheHandlerSelectsNonzeroEntry(D_800D0138, state, context);
    state->callback = (void *)townUpdateThresholdCountdownWithBusyCheck;
    state->count = 6;
}
