#include "modules/dungeon_ovl_cd7000.h"

void func_8014FB64(S_80173B64_0 *state,void *position,void *render_state,void *entity) {
    if (dungeonInterpolateActorToTerrainTile(state,position,render_state,entity) != 0) {
        state->CL_CD7000_80173B64_handler = func_8014D02C;
    }
}
