#include "modules/dungeon_ovl_cc5000.h"

void func_801603DC(void *state_arg,void *position,void *render_state,void *entity) {
    S_801723DC_0 *state=state_arg;
    if (update_actor_movement_to_tile(state,position,render_state,entity) != 0) {
        reduce_actor_food_meter(entity, 4);
        advance_status_timers(entity);
        if ((check_actor_floor_trap(render_state, entity) << 0x10) > 0) {
            state->CL_CC5000_801723DC_unk_8C = func_8015F02C;
            state->unk_90 = 0;
        }
    }
}
