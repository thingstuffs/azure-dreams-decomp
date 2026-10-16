#include "modules/dungeon_ovl_ccb000.h"

void func_8015B364(S_80173364_0 *state,void *position,void *render_state,void *entity) {
    if (dungeonUpdateActorHopAndGrow(state,position,render_state,entity) != 0) {
        state->CL_CCB000_80173364_handler = func_8015902C;
    }
}
