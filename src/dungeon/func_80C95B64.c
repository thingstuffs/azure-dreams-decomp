#include "modules/dungeon_ovl_cb3000.h"

void func_80173364(S_80173364_0 *state,void *position,void *render_state,void *entity) {
    if (update_actor_hop_and_grow(state,position,render_state,entity) != 0) {
        state->CB_80173364_handler = func_8017102C;
    }
}
