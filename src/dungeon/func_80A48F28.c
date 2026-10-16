#include "modules/dungeon_resource06_slot0.h"

void func_80172728(Resource06CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateLinkedActorMotion(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = func_8017140C;
        }
    }
}
