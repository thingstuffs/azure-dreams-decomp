#include "modules/dungeon_ovl_16b08_local.h"

void func_8009451C(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context) {
    townCallTheHandlerSelectsNonzeroEntry(D_800D0128, state, context);
    state->callback = (void *)townUpdateActorMovementAndInteraction;
}
