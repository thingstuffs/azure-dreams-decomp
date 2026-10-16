#include "modules/dungeon_ovl_cc5000.h"

void func_80161BD4(S_80173BD4_0 *state,void *position,void *render_state,void *entity) {
    if (func_800ACE34(state,position,render_state) != 0) {
        state->CL_CC5000_80173BD4_handler = func_8015F02C;
    }
}
