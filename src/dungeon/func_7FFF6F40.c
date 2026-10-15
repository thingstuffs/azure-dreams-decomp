#include "modules/dungeon_ovl_16b08_local.h"

void func_800946A0(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context) {
    func_80094C1C(state, argument, context);
    func_80094984(D_800D0138, state, context);
    state->callback = (void *)func_80092FF0;
    state->count = 6;
}
