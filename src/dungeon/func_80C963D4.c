#include "modules/dungeon_ovl_cb3000.h"

void func_80173BD4(S_80173BD4_0 *state,void *position,void *render_state,void *entity) {
    if (dungeonUpdateActorFadeIn(state,position,render_state) != 0) {
        state->CB_80173BD4_handler = func_8017102C;
    }
}
