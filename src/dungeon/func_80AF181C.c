#include "modules/dungeon_resource10_slot0.h"

void func_8017301C(Resource10CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateLinkedActorMotion(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = func_801717F4;
        }
    }
}
