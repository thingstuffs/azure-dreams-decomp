#include "modules/dungeon_ovl_ccb000.h"

void func_8015A944(S_80172944_0 *state,void *position,void *render_state,void *entity) {
    if ((func_800AB378(state,position,render_state,entity) != 0) && ((func_800AD9B4(render_state, entity) << 0x10) > 0)) {
        state->CL_CCB000_80172944_handler = func_8015902C;
    }
}
