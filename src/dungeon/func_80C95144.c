#include "modules/dungeon_ovl_cb3000.h"

void func_80172944(S_80172944_0 *state,void *position,void *render_state,void *entity) {
    if ((dungeonUpdateLinkedActorMotion(state,position,render_state,entity) != 0) && ((dungeonCheckActorFloorTrap(render_state, entity) << 0x10) > 0)) {
        state->CB_80172944_handler = func_8017102C;
    }
}
