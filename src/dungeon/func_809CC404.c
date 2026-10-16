#include "modules/dungeon_resource03_slot0.h"

void func_80173C04(Resource03CallbackState *state, void *motion, void *position, void *actor)
{
    if (dungeonResolveActorFloorTrapOnce(state, motion, position, actor) > 0) {
        state->callback = func_80170E54;
    }
}
