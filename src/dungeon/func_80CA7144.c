#include "modules/dungeon_ovl_cc5000.h"

void func_80160944(S_80172944_0 *state,void *position,void *render_state,void *entity) {
    if ((update_linked_actor_motion(state,position,render_state,entity) != 0) && ((check_actor_floor_trap(render_state, entity) << 0x10) > 0)) {
        state->CL_CC5000_80172944_handler = func_8015F02C;
    }
}
