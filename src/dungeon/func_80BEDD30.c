#include "modules/dungeon_resource16_slot0.h"

void func_80173530(Resource16CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateThrownActorTravel(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = func_80171014;
        }
    }
}
