#include "modules/dungeon_ovl_ccb000.h"

void func_8015A3DC(void *state_arg,void *position,void *render_state,void *entity) {
    S_801723DC_0 *state=state_arg;
    if (dungeonUpdateActorMovementToTile(state,position,render_state,entity) != 0) {
        dungeonReduceActorFoodMeter(entity, 4);
        dungeonAdvanceStatusTimers(entity);
        if ((dungeonCheckActorFloorTrap(render_state, entity) << 0x10) > 0) {
            state->CL_CCB000_801723DC_unk_8C = func_8015902C;
            state->unk_90 = 0;
        }
    }
}
