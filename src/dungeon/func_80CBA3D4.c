#include "modules/dungeon_ovl_cd7000.h"

void func_8014FBD4(S_80173BD4_0 *state,void *position,void *render_state,void *entity) {
    if (update_actor_fade_in(state,position,render_state) != 0) {
        state->CL_CD7000_80173BD4_handler = func_8014D02C;
    }
}
