#include "modules/dungeon_resource07_slot0.h"

void func_801740C8(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonResolveActorFloorTrapOnce(state, motion, position, actor) > 0) {
        state->callback = func_80170E54;
    }
}
