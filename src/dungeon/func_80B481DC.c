#include "modules/dungeon_resource12_slot0.h"

void func_801759DC(Resource12CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonResolveActorFloorTrapOnce(state, motion, position, actor) > 0) {
        state->callback = func_80170E70;
    }
}
