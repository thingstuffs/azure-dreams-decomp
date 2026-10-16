#include "modules/dungeon_ovl_cd7000.h"

void func_8014F364(S_80173364_0 *state,void *position,void *render_state,void *entity) {
    if (func_800ABDBC(state,position,render_state,entity) != 0) {
        state->CL_CD7000_80173364_handler = func_8014D02C;
    }
}
