#include "modules/dungeon_resource10_slot0.h"

void dungeonAdvanceBossCommandStream(Resource10CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateThrownActorTravel(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = func_801717F4;
        }
    }
}
