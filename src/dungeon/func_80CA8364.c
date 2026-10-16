#include "modules/dungeon_ovl_cc5000.h"

void func_80161B64(S_80173B64_0 *state,void *position,void *render_state,void *entity) {
    if (dungeonInterpolateActorToTerrainTile(state,position,render_state,entity) != 0) {
        state->CL_CC5000_80173B64_handler = func_8015F02C;
    }
}
