#include "modules/dungeon_ovl_cb9000.h"

void func_8016D364(S_80173364_0 *state,void *position,void *render_state,void *entity) {
    if (update_actor_hop_and_grow(state,position,render_state,entity) != 0) {
        state->CL_CB9000_80173364_handler = func_8016B02C;
    }
}
