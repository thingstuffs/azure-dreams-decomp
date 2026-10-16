#include "modules/dungeon_ovl_cb9000.h"

void func_8016DB9C(S_80173B9C_0 *state,void *position,void *render_state,void *entity) {
    if (dungeonUpdateSpinningActorFall(state,position,render_state,entity) != 0) {
        state->CL_CB9000_80173B9C_handler = func_8016B02C;
    }
}
