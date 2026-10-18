#include "modules/dungeon_ovl_cc5000.h"

void func_80161B00(S_80173B00_0 *state,void *position,void *render_state,void *entity) {
    if ((update_thrown_actor_travel(state,position,render_state,entity) != 0) && ((check_actor_floor_trap(render_state, entity) << 0x10) > 0)) {
        state->CL_CC5000_80173B00_handler = func_8015F02C;
    }
}
