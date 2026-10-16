#include "modules/dungeon_resource08_slot0.h"

void func_80173FE8(Resource08CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateThrownActorTravel(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = dungeonUpdateActorBehaviorAndEffect;
        }
    }
}
