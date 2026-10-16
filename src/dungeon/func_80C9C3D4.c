#include "modules/dungeon_ovl_cb9000.h"

void func_8016DBD4(S_80173BD4_0 *state,void *position,void *render_state,void *entity) {
    if (dungeonUpdateActorFadeIn(state,position,render_state) != 0) {
        state->CL_CB9000_80173BD4_handler = func_8016B02C;
    }
}
