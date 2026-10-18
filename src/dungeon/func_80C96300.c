#include "modules/dungeon_ovl_cb3000.h"

void func_80173B00(S_80173B00_0 *state,void *position,void *render_state,void *entity) {
    if ((update_thrown_actor_travel(state,position,render_state,entity) != 0) && ((check_actor_floor_trap(render_state, entity) << 0x10) > 0)) {
        state->CB_80173B00_handler = func_8017102C;
    }
}
