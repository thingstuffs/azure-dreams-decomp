#include "modules/dungeon_ovl_16b08_local.h"

void func_80094660(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context) {
    func_80094984(D_800D00B8, state, context);
    state->callback = (void *)func_80092ECC;
}
