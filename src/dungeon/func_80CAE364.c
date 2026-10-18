#include "modules/dungeon_ovl_ccb000.h"

void func_8015BB64(S_80173B64_0 *state,void *position,void *render_state,void *entity) {
    if (interpolate_actor_to_terrain_tile(state,position,render_state,entity) != 0) {
        state->CL_CCB000_80173B64_handler = func_8015902C;
    }
}
