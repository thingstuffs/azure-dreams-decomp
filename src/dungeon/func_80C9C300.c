#include "modules/dungeon_ovl_cb9000.h"

void func_8016DB00(S_80173B00_0 *state,void *position,void *render_state,void *entity) {
    if ((func_800AC010(state,position,render_state,entity) != 0) && ((func_800AD9B4(render_state, entity) << 0x10) > 0)) {
        state->CL_CB9000_80173B00_handler = func_8016B02C;
    }
}
