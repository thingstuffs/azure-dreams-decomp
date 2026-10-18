#include "modules/dungeon_ovl_ccb000.h"

void func_8015BBD4(S_80173BD4_0 *state,void *position,void *render_state,void *entity) {
    if (update_actor_fade_in(state,position,render_state) != 0) {
        state->CL_CCB000_80173BD4_handler = func_8015902C;
    }
}
