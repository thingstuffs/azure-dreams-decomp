#include "modules/dungeon_ovl_ccb000.h"

void func_8015BB9C(S_80173B9C_0 *state,void *position,void *render_state,void *entity) {
    if (update_spinning_actor_fall(state,position,render_state,entity) != 0) {
        state->CL_CCB000_80173B9C_handler = func_8015902C;
    }
}
