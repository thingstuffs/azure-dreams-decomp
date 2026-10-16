#include "modules/dungeon_ovl_16b08_local.h"

void func_80094474(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context) {
    townCallTheHandlerSelectsNonzeroEntry(D_800D0118, state, context);
    state->callback = (void *)func_80090E78;
    state->count = 6;
}
