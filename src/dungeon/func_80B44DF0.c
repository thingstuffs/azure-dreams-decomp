#include "modules/dungeon_resource12_slot0.h"

void dungeonCheckBossEffectThreshold(Resource12CallbackState *state, void *entity, void *position, void *graphic)
{
    if (dungeonUpdateLinkedActorMotion(state, entity, position, graphic)) {
        if ((s16)dungeonCheckActorFloorTrap(position, graphic) > 0) {
            state->callback = func_80170E70;
        }
    }
}
