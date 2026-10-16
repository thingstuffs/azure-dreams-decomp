#include "modules/dungeon_ovl_cb9000.h"

void func_8016DB64(S_80173B64_0 *state,void *position,void *render_state,void *entity) {
    if (func_800AC480(state,position,render_state,entity) != 0) {
        state->CL_CB9000_80173B64_handler = func_8016B02C;
    }
}
